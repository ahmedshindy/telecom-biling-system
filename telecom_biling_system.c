#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aio.h>
#include "telecom_biling_system.h"

#define MAZ_LINE_SIZE   100


/*struct of data */
char* name ;
size_t name_size = 30;
char* phone_number;
size_t phone_number_size;
float amount;


static int generate_id(const char* name_ptr);
static int get_id_from_line( char* LineBuff);

FILE *fptr;

// need to be stored in eeprom or txt file
// size_t records_counter = 1;


/* this function lists the available options */
void show_menu(void)
{
    // loop on menu struct (optional)

    /* Main Menu */
    printf("choose Option \n \
    1- Add new Record\n \
    2- View Records\n \
    3- Modify Record \n \
    4- View Payment\n \
    5- Exit\n");
    return;
}


/*
@brief : This function reads new record, name , phone , and amount to pay;
*/
void read_record(void)
{

   // static char* new_name = (char*) malloc(name_size * sizeof(char));
    name = (char*) malloc(name_size * sizeof(char));
    phone_number = (char*) malloc(phone_number_size * sizeof(char));

    /* get name, id, phone number, amount_to_pay */
    printf("Enter Name: ");
    getline(&name,&name_size, stdin);
    printf("Enter phone number: ");
    getline(&phone_number,&phone_number_size, stdin);
    printf("Enter amount: ");
    scanf("%f",&amount);
}

void store_new_record(void)
{
    int ID=0;
    // store entity 
    fptr = fopen("database.txt","a+");
    if(fptr == NULL)
    {
        printf("Error!");   
        exit(1);             
    }
    size_t record_name_size = strlen(name);
    size_t record_phone_size = strlen(phone_number);

    /* Remove the new line charachter (\n) from the name */
    name[record_name_size -1] = '\0';
    /*generate id from user name, not including new line char */
    ID =generate_id(name);


    /* Remove the new line charachter (\n) from the phonenumber */
    phone_number[record_phone_size -1] = '\0';

    //do optimization & write entity to file 
    fprintf(fptr,"%d,%s,%s,%0.4f\n",ID,name, phone_number,amount);

    free(name);
    free(phone_number);
    amount = 0.0;
    fclose(fptr);
}


/* This function prints a comma separated values (csv) file to the console */
void view_records(void)
{
    char* line;
    ssize_t chars_read =0;
    size_t len = (name_size + phone_number_size + 50);
    fptr = fopen("database.txt","r");
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
void modify_record()
{

    char * new_name;
    char* new_number;
    float new_amount;
    char * line_buffer= NULL;
    ssize_t returned_line_size=0;
    size_t RecordId=0;
    size_t LineId = 0;
    size_t line_counter= 1;
    size_t max_line_size =100;
    char temp_char;

    name = (char*) malloc(name_size * sizeof(char));
    FILE* temp_fp = fopen("deatabase_temp.txt","w");
    FILE* fp = fopen("database.txt","r");
    if (  (!fp) || (!temp_fp) )
    {
        fprintf(stderr, "Error opening file database file\n");
        return ;
    }


    // read line number "same as record ID "
    printf("Enter record Name: ");
    getline(&name,&name_size, stdin);

    size_t record_name_size = strlen(name);
    name[record_name_size -2] = '\0';
    RecordId = generate_id(name);


    printf("generated id is: %ld\n",RecordId);
    return ;

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
        returned_line_size = getline(&line_buffer,&max_line_size,fp);
        LineId = get_id_from_line(line_buffer);
        // modify condition
        if(LineId== RecordId)
        {
            // modify this line, then write it 
            printf("Enter New name: ");


        }
        else if (feof(fp))
        {
            break;
        }
        else
        {
            // write line_buffer to the temp_file
            fputs(line_buffer,temp_fp);
        }
        // exit condition 
    }

    fclose(fp);
    fclose(temp_fp);

    remove("database.txt"); // use variables
    rename("database_temp.txt","database.txt");

}


static int generate_id(const char*  name_ptr)
{
	int size=strlen(name_ptr);
	int sum=0;
	for(int i=0; i< size ; i++)
		sum+= name_ptr[i];
	return sum;
}

static int get_id_from_line(char* LineBuff)
{
    int local_id =0;
    // begin tokenizing sentence
    char *tokenPtr = strtok(LineBuff,"-"); 
	// while (tokenPtr != NULL)
	// {
	// 	tokenPtr = strtok(NULL, " "); 
	// }

    local_id= atoi(tokenPtr);
    return local_id;

}
