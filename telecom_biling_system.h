#ifndef TELECOM_BILING_SYSTEM_H
#define TELECOM_BILING_SYSTEM_H

// #define MAX_LINE_LENGTH 1000U
// typedef struct User
// {
//     size_t id;
//     float amout;
//     char* name;
//     char* phone_number;

// }User_t;


// struct BilingSystem
// {
//     void(*ShowMenu)(void);

// }BilingSystem_t;


#define SUCCEEDED   0
#define NOT_SUCCEEDED   1


/*struct of data */
typedef struct record
{
char name[50] ;
char phone_number[50];
float amount;
}record_t;



/*functions */
int show_menu(void);
// void read_record(void);
int read_record(record_t* record_entity);

int store_new_record(record_t* ptr_record_entity);
// void view_records(const FILE* dbPtr )
void view_records(void);
void modify_record();


#endif