#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aio.h>
#include "telecom_biling_system.h"

#define MAZ_LINE_SIZE   100
size_t name_size = 30;
size_t phone_number_size =30;

/* this function lists the available options */
int show_menu(void)
{
    /* Main Menu */
    printf("choose Option \n \
    1- Add new Record\n \
    2- View Records\n \
    3- Modify Record \n \
    4- View Payment\n \
    5- Exit\n");
    return SUCCEEDED;
}

// This function reads new record, name , phone , and amount to pay
int read_record(record_t * ptr_record_entity)
{

    char* name = (char*) malloc(name_size * sizeof(char));
    char* phone_number = (char*) malloc(phone_number_size * sizeof(char));
    double amount;
    /* get name, id, phone number, amount_to_pay */
    printf("Enter Name: ");
    fflush(stdin);
    getline(&name,&name_size, stdin);
    printf("Enter phone number: ");
    fflush(stdin);
    getline(&phone_number,&phone_number_size, stdin);
    printf("Enter amount: ");
    fflush(stdin);
    scanf("%lf",&amount);

    /*remove newline char from name and phone number */
    size_t name_len= strlen(name);
    name[name_len-1]= '\0';
    size_t phone_len = strlen(phone_number);
    phone_number[phone_len-1]= '\0';

    strncpy(ptr_record_entity->name,name,name_len);
    strncpy(ptr_record_entity->phone_number,phone_number,phone_len);
    ptr_record_entity->amount= amount;

    ptr_record_entity->name[name_len]='\0';
    ptr_record_entity->phone_number[phone_len]='\0';

    free(name);
    free(phone_number);
    return SUCCEEDED;
}

int store_new_record(record_t* ptr_record_entity)
{
    int ID=0;
    FILE* db_fptr = fopen("database_db.txt","a+");
    if(db_fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }
    /* generate id from user name */
    ID =generate_id(ptr_record_entity->name);
    // write entity to csv file 
    fprintf(db_fptr,"%d,%s,%s,%0.4lf\n",ID,(char*)ptr_record_entity->name,
             (char*)ptr_record_entity->phone_number,ptr_record_entity->amount);
    fclose(db_fptr);
}

/* This function prints a comma separated values (csv) file to the console */
void view_records(void)
{
    char* line;
    ssize_t chars_read =0;
    size_t len = 150;
   FILE* fptr = fopen("database_db.txt","r");
    if(fptr == NULL)
    {
        printf("No database found\n");
    }
    else
    {
        while (chars_read = getline(&line,&len,fptr) != -1)
        {
            printf("%s",line);
        }
        
    }
    printf("\n\n");
    fclose(fptr);
    return;
}


/* This function modifies the amount of payment of a specific user */
void modify_record(size_t Record_ID)
{

    record_t new_entity;
    char * line_buffer= NULL;
        size_t max_line_size =100;

    char TembBuffer[max_line_size];
    ssize_t returned_line_size=0;
    size_t line_counter= 1;
    char temp_char;


    printf("Enter new data...\n");
    fflush(stdin); // name is null ? newline 
    scanf("%c",&temp_char);
    fflush(stdout);
    read_record(&new_entity);
    fflush(stdin);
    size_t newID = generate_id(new_entity.name);
    FILE* temp_fp = fopen("database_temp.txt","a+");
    FILE* Old_fp = fopen("database_db.txt","r");
    if (  (!Old_fp) || (!temp_fp) )
    {
        fprintf(stderr, "Error opening database file\n");
        return ;
    }


    // // temp read line number "same as record ID "
    // printf("Enter record Name: ");
    // getline(&name,&name_size, stdin);
    // size_t record_name_size = strlen(name);
    // name[record_name_size -2] = '\0';
    // RecordId = generate_id(name);
    // printf("generated id is: %ld\n",RecordId);
    // return ;
    // while( (RecordId >= records_counter) || (RecordId <0)) 
    // {
    //     printf("Id not found, try again\n\
    //     Enter record Id: ");
    //     getline(&name,&name_size, stdin);
    //         /*Check if user wants to exit this option*/
    //         if(RecordId == 0)
    //         {
    //             return;
    //         }
    // }

    while(1)
    {
        // read the file line by line
        returned_line_size = getline(&line_buffer,&max_line_size,Old_fp);

        size_t line_len = strlen(line_buffer);
        line_buffer[line_len] = '\0';
        size_t LineId =0;
        strncpy(TembBuffer,line_buffer,line_len+1); // +1 for the null terminator
        // for(int i =0; (i<line_len) && (i<max_line_size) ; i++)
        // {
        //     if(line_buffer[i] != ',')   LineId+=(size_t)(line_buffer[i]);
        //     else                        break;
        // }

        char *tokenPtr = strtok(line_buffer,","); 
        LineId = atoi(tokenPtr);
        if (feof(Old_fp))
        {
            break;
        }
        else  if(LineId == Record_ID)
        {
            // modify this line, then write it 
            fprintf(temp_fp,"%ld,%s,%s,%0.4lf\n",newID,(char*)new_entity.name,
             (char*)new_entity.phone_number,new_entity.amount);
        }
        else
        {
            // write line_buffer to the temp_file
            fprintf(temp_fp,"%s,,,\n",TembBuffer); // only writes one char err?
        }
    }

    fclose(Old_fp);
    fclose(temp_fp);

    remove("database_db.txt"); // use variables
    
    if (rename("database_temp.txt","database_db.txt") == 0)
    {
        printf("file renamed\n");
    }
    else
    {
        printf("file is not renamed\n");
    }
}

/*this function views the payment of a specific user, taking its id */
void view_payments(void)
{

    char line_buffer[100];
    char loc_name[50];
    printf("Enter user name: ");
    fflush(stdin);
    // scanf("%s",loc_name); 
    size_t max_line_size = 200;

    // remove \n from input name
    size_t name_len = strlen(loc_name);
    loc_name[name_len-1]= '\0';


    int id = generate_id(loc_name);
    FILE* db_fptr= fopen("database_db.txt","r");

    while( getline((char**)&line_buffer,&max_line_size,db_fptr) != -1)
    {
        if( get_id_from_line(line_buffer) == id )
        {
            printf("%s\n",line_buffer);
        }
    }

    printf("Record does not exist\n");

    return;
}

int generate_id(const char*  name_ptr)
{
	int size=strlen(name_ptr);
	int sum=0;
	for(int i=0; i< size ; i++)
		sum+= name_ptr[i];
	return sum;
}

int get_id_from_line(char* LineBuff)
{
    char *tokenPtr = strtok(LineBuff,","); 
    int local_id= atoi(tokenPtr);
    return local_id;
}
