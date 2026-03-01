/*Name : Vaishnavi R Hujaratti
User Id : 25017_269
Project name : Inverted Search
Date : 22/11/25
*/
#include "inverted.h"

/*
 * ==========================================================================
 * FUNCTION: main
 * --------------------------------------------------------------------------
 * Purpose:
 *      Controls the whole program.
 *      Shows menu and calls CREATE, DISPLAY, SEARCH, UPDATE, SAVE.
 *
 * Special Rules (as your sir wants):
 *      1) create → create  ❌ not allowed
 *      2) create → update  ❌ not allowed
 *      3) update → update  ❌ not allowed
 *      4) update → create  ✔ allowed
 *
 * Uses two flags:
 *      create_done = 1 when CREATE is used
 *      update_done = 1 when UPDATE is used
 * ==========================================================================
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./a.out file1.txt file2.txt ...\n");
        return 0;
    }

    hash_table htable[26] = {0};
    for (int i = 0; i < 26; i++) htable[i].key = i;

    Fnode *file_list = NULL;
    if (validate_and_store_files(&file_list, argv, argc) == FAILURE)
        return 0;

    int create_done = 0;
    int update_done = 0;

    while (1)
    {
        printf("\n----- MENU -----\n");
        printf("1. CREATE DATABASE\n");
        printf("2. DISPLAY DATABASE\n");
        printf("3. SEARCH DATABASE\n");
        printf("4. UPDATE (RESTORE)\n");
        printf("5. SAVE DATABASE\n");
        printf("6. EXIT\n");
        printf("Enter choice: ");

        int ch;
        scanf("%d", &ch);

        if (ch == 1)   // CREATE
        {
            if (create_done)
            {
                printf("ERROR: Cannot CREATE twice.\n");
                continue;
            }
            if (update_done)
                printf("INFO: Creating new DB after update.\n");

            create_database(htable, file_list);
            create_done = 1;
        }

        else if (ch == 2)
            display_database(htable);

        else if (ch == 3)
        {
            char w[MAXW];
            printf("Enter word: ");
            scanf("%s", w);
            search_database(htable, w);
        }

        else if (ch == 4)   // UPDATE
        {
            if (update_done)
            {
                printf("ERROR: Cannot UPDATE twice.\n");
                continue;
            }
            if (create_done)
            {
                printf("ERROR: Cannot UPDATE after CREATE.\n");
                continue;
            }

            char fname[MAXF];
            printf("Enter backup file: ");
            scanf("%s", fname);

            if (restore_database_from_backup(htable, fname) == SUCCESS)
                update_done = 1;
        }

        else if (ch == 5)
        {
            char out[MAXF];
            printf("Save as: ");
            scanf("%s", out);
            save_database(htable, out);
        }

        else if (ch == 6)
        {
            printf("Exiting...\n");
            break;
        }

        else
            printf("Invalid choice.\n");
    }

    return 0;
}
