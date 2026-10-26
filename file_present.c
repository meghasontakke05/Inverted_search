#include "inverted_search.h"
int is_file_present(hashtable *ht, char *filename)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        mainnode *m_temp = ht->table[i];

        while (m_temp != NULL)
        {
            subnode *s_temp = m_temp->sublink;

            while (s_temp != NULL)
            {
                if (strcmp(s_temp->file_name, filename) == 0)
                {
                    return SUCCESS;
                }

                s_temp = s_temp->link;
            }

            m_temp = m_temp->link;
        }
    }

    return FAILURE;
}