#include "inverted_search.h"
int display_database(hashtable *ht)
{
    if(ht==NULL)
    {
        printf("Hash table is NULL\n ");
        return FAILURE;
    }
    printf("\n-----------------------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-12s %-20s %-10s\n", "Index","Word","File Count","File Name","Word Count");
    printf("-----------------------------------------------------------------------------------------\n");

    int found=0;

    for(int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *mtemp = ht->table[i];

        while(mtemp != NULL)
        {
            found=1;
            subnode *stemp = mtemp->sublink;
            int first = 1;

            while(stemp != NULL)
            {
                if(first)
                {
                    printf("%-10d %-15s %-12d %-20s %-10d\n",i, mtemp->word,mtemp->file_count,stemp->file_name,stemp->word_count);

                    first = 0;
                }
                else
                {
                    printf("%-10s %-15s %-12s %-20s %-10d\n","","","",stemp->file_name,stemp->word_count);
                }

                stemp = stemp->link;
            }

            printf("\n");
            mtemp = mtemp->link;
        }
    }
    if(found==0)
    {
        printf("\n\tDatabase is empty\n");
    }

    printf("-----------------------------------------------------------------------------------------\n");

    return SUCCESS;
}