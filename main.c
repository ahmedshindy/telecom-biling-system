#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <aio.h>
#include "telecom_biling_system.h"




record_t entity;
char char_temp;
int choice = 0;
int main()
{
    int Err_state= NOT_SUCCEEDED;
    /* Show Menu at Startup */
    show_menu();
    while (1)
    {
        /* Read and Switch on the choice */
        printf("Choice: ");
        scanf("%d",&choice);
        /*read the remaining new line char int the input buffer */
        scanf("%c",&char_temp);
        printf("\n");
        switch (choice)
        {
            case 1:
            {
                Err_state= read_record(&entity);
                if(Err_state == SUCCEEDED)
                {
                    store_new_record(&entity);
                }
                break;
            }
            case 2:
                /*Show available records */
                view_records();
                break;
            case 3:
                // modify record full data: name, phone, amount of payment
                // modify_record();
                break;
            case 4:
                break;
            case 5:
                printf("Shutting down...\n");
                return 0;
            default:

                printf("Invalid Option, enter valid option\n");
                break;
        }
        printf("Enter Another Option: ");
        choice = 5;
    }

    return 0;
}
