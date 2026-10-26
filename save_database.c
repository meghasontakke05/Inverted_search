#include "inverted_search.h"

int save_database(hashtable *ht)
{
    char filename[50];

    /* Read backup file name */
    printf("Enter backup file name: ");
    scanf("%s", filename);

    /* Validate extension */
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Invalid file extension\n");
        return FAILURE;
    }

    /* Open file in write mode */
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Unable to open file\n");
        return FAILURE;
    }

    /* Traverse hash table */
    for (int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *mtemp = ht->table[i];

        while (mtemp != NULL)
        {
            /* Write index, word and file count */
            fprintf(fp, "#%d;%s;%d;",i,mtemp->word,mtemp->file_count);

            /* Traverse subnode */
            subnode *stemp = mtemp->sublink;

            while (stemp != NULL)
            {
                fprintf(fp, "%s;%d;",stemp->file_name,stemp->word_count);

                stemp = stemp->link;
            }

            fprintf(fp, "#\n");

            mtemp = mtemp->link;
        }
    }

    fclose(fp);

    printf("Database saved successfully.\n");

    return SUCCESS;
}