#include "inverted_search.h"

int search_database(hashtable *ht)
{
    char search_word[50];

    printf("Enter the word to search: ");
    scanf("%s", search_word);

    /* Find index */
    int index;

    if (search_word[0] >= 'a' && search_word[0] <= 'z')
    {
        index = search_word[0] - 'a';
    }
    else
    {
        index = 26;
    }

    /* Check whether index is empty */
    if (ht->table[index] == NULL)
    {
        printf("\nWord \"%s\" not found.\n", search_word);
        return FAILURE;
    }

    /* Traverse main nodes */
    mainnode *mtemp = ht->table[index];

    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, search_word) == 0)
        {
            printf("\nWord        : %s\n", mtemp->word);
            printf("File Count  : %d\n", mtemp->file_count);

            printf("--------------------------------------\n");
            printf("%-20s %-10s\n", "File Name", "Word Count");
            printf("--------------------------------------\n");

            subnode *stemp = mtemp->sublink;

            while (stemp != NULL)
            {
                printf("%-20s %-10d\n",stemp->file_name,stemp->word_count);

                stemp = stemp->link;
            }

            printf("--------------------------------------\n");

            return SUCCESS;
        }

        mtemp = mtemp->link;
    }

    printf("\nWord \"%s\" not found.\n", search_word);

    return FAILURE;
}