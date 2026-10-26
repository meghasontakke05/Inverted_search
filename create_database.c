#include "inverted_search.h"

int create_database(hashtable *ht, filelist *head)
{
    FILE *fp;
    char word[100];
    int index;

    filelist *f_temp = head;

    /* Traverse all files */
    while (f_temp != NULL)
    {
        /* Skip files already loaded through update database */
    if (is_file_present(ht, f_temp->file_name) == SUCCESS)
    {
        printf("%s already updated. Skipping...\n", f_temp->file_name);
        f_temp = f_temp->link;
        continue;
    }

        fp = fopen(f_temp->file_name, "r");

        if (fp == NULL)
        {
            f_temp = f_temp->link;
            continue;
        }

        /* Read every word from current file */
        while (fscanf(fp, "%99s", word) != EOF)
        {
            index = hash_function(word);

            /************ CASE 1 : HASH INDEX EMPTY ************/
            if (ht->table[index] == NULL)
            {
                mainnode *m_new = malloc(sizeof(mainnode));
                if (m_new == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                subnode *s_new = malloc(sizeof(subnode));
                if (s_new == NULL)
                {
                    free(m_new);
                    fclose(fp);
                    return FAILURE;
                }

                m_new->word = malloc(strlen(word) + 1);
                if (m_new->word == NULL)
                {
                    free(s_new);
                    free(m_new);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(m_new->word, word);

                s_new->file_name = malloc(strlen(f_temp->file_name) + 1);
                if (s_new->file_name == NULL)
                {
                    free(m_new->word);
                    free(s_new);
                    free(m_new);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(s_new->file_name, f_temp->file_name);

                s_new->word_count = 1;
                s_new->link = NULL;

                m_new->file_count = 1;
                m_new->sublink = s_new;
                m_new->link = NULL;

                ht->table[index] = m_new;
            }

            /************ HASH INDEX NOT EMPTY ************/
            else
            {
                mainnode *m_temp = ht->table[index];
                mainnode *prev = NULL;

                /* Search word */
                while (m_temp != NULL)
                {
                    if (strcmp(m_temp->word, word) == 0)
                        break;

                    prev = m_temp;
                    m_temp = m_temp->link;
                }

                /************ CASE 2 : WORD FOUND ************/
                if (m_temp != NULL)
                {
                    subnode *s_temp = m_temp->sublink;

                    /* Search file name */
                    while (s_temp != NULL)
                    {
                        if (strcmp(s_temp->file_name, f_temp->file_name) == 0)
                            break;

                        s_temp = s_temp->link;
                    }

                    /* File already exists */
                    if (s_temp != NULL)
                    {
                        s_temp->word_count++;
                    }

                    /************ CASE 3 : NEW FILE ************/
                    else
                    {
                        subnode *s_new = malloc(sizeof(subnode));

                        if (s_new == NULL)
                        {
                            fclose(fp);
                            return FAILURE;
                        }

                        s_new->file_name = malloc(strlen(f_temp->file_name) + 1);

                        if (s_new->file_name == NULL)
                        {
                            free(s_new);
                            fclose(fp);
                            return FAILURE;
                        }

                        strcpy(s_new->file_name, f_temp->file_name);

                        s_new->word_count = 1;

                        s_new->link = m_temp->sublink;
                        m_temp->sublink = s_new;

                        m_temp->file_count++;
                    }
                }

                /************ CASE 4 : WORD NOT FOUND ************/
                else
                {
                    mainnode *m_new = malloc(sizeof(mainnode));

                    if (m_new == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    subnode *s_new = malloc(sizeof(subnode));

                    if (s_new == NULL)
                    {
                        free(m_new);
                        fclose(fp);
                        return FAILURE;
                    }

                    m_new->word = malloc(strlen(word) + 1);

                    if (m_new->word == NULL)
                    {
                        free(s_new);
                        free(m_new);
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(m_new->word, word);

                    s_new->file_name = malloc(strlen(f_temp->file_name) + 1);

                    if (s_new->file_name == NULL)
                    {
                        free(m_new->word);
                        free(s_new);
                        free(m_new);
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(s_new->file_name, f_temp->file_name);

                    s_new->word_count = 1;
                    s_new->link = NULL;

                    m_new->file_count = 1;
                    m_new->sublink = s_new;
                    m_new->link = NULL;

                    /* Insert at end of main node list */

                    if (prev == NULL)
                    {
                        ht->table[index] = m_new;
                    }
                    else
                    {
                        prev->link = m_new;
                    }
                }
            }
        }

        fclose(fp);

        f_temp = f_temp->link;
    }

    return SUCCESS;
}