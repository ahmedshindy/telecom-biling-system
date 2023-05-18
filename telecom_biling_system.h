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



/*functions */
void show_menu(void);
void read_record(void);
void store_new_record(void);
// void view_records(const FILE* dbPtr )
void view_records(void);
void modify_record();


#endif