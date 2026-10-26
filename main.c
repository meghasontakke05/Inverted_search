#include "inverted_search.h"
#include<stdio.h>


int main(int argc, char *argv[])
{
    hashtable ht = {NULL};

    filelist *head = NULL;

    /* Validate command line arguments */
    if (argc < 2)
    {
        printf("ERROR: Pass the file names.\n");
        printf("Usage: ./a.out file1.txt file2.txt ...\n");
        return FAILURE;
    }

    /* Validate each file */
    for (int i = 1; i < argc; i++)
    {
        if (validation(argv[i], &head) == SUCCESS)
        {
            printf("%s : Validation Successful\n", argv[i]);
        }
        else
        {
            printf("%s : Validation Failed\n", argv[i]);
        }
    }

    int choice;
    char word[50];
    char backup_file[50];
    int create_flag=0;
    int update_flag=0;

    while (1)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (create_flag)
    {
        printf("Database is already created.\n");
        break;
    }

    if (create_database(&ht, head) == SUCCESS)
    {
        printf("Database created successfully.\n");
        create_flag = 1;
    }
    else
    {
        printf("Database creation failed.\n");
    }
                break;

            case 2:
                display_database(&ht);
                break;

            case 3:
                search_database(&ht);
                break;

            case 4:
                save_database(&ht);
                break;

            case 5:
                 if (create_flag == 1)
    {
        printf("Database already created. Update not allowed.\n");
    }
    else if (update_flag == 1)
    {
        printf("Database is already updated.\n");
    }
    else
    {
        printf("Enter backup file name : ");
        scanf("%s", backup_file);

        if (update_database(&ht, backup_file) == SUCCESS)
        {
            printf("Database updated successfully.\n");
            update_flag = 1;
        }
        else
        {
            printf("Database update failed.\n");
        }
    }
                break;

            case 6:
                printf("Thank You...\n");
                return SUCCESS;

            default:
                printf("Invalid Choice\n");
        }
    }
}