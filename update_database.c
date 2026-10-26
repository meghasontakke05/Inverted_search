#include "inverted_search.h"

int update_database(hashtable *ht, char *filename)
{
    /* Validate extension */
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Invalid file extension\n");
        return FAILURE;
    }

    /* Open backup file */
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return FAILURE;
    }

    /* Check whether file is empty */
    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        printf("Backup file is empty\n");
        fclose(fp);
        return FAILURE;
    }

    rewind(fp);

    char line[500];

    /* Read each record */
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';

        /* Validate backup format */
        if (line[0] != '#')
        {
            printf("Invalid backup file format\n");
            fclose(fp);
            return FAILURE;
        }

        /* Remove first '#' */
        memmove(line, line + 1, strlen(line));

        int len = strlen(line);

        /* Remove last '#' */
        if (line[len - 1] == '#')
        {
            line[len - 1] = '\0';
        }

        /* Tokenize */
        char *token = strtok(line, ";");

        if (token == NULL)
            continue;

        int index = atoi(token);

        /* Word */
        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        char word[100];
        strcpy(word, token);

        /* File count */
        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        int file_count = atoi(token);

        /* Create Main Node */
        mainnode *mnew = malloc(sizeof(mainnode));

        if (mnew == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        mnew->word = malloc(strlen(word) + 1);

        if (mnew->word == NULL)
        {
            free(mnew);
            fclose(fp);
            return FAILURE;
        }

        strcpy(mnew->word, word);

        mnew->file_count = file_count;
        mnew->sublink = NULL;
        mnew->link = NULL;

        subnode *last = NULL;

        /* Create Sub Nodes */
        for (int i = 0; i < file_count; i++)
        {
            subnode *snew = malloc(sizeof(subnode));

            if (snew == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            /* File name */
            token = strtok(NULL, ";");

            snew->file_name = malloc(strlen(token) + 1);

            if (snew->file_name == NULL)
            {
                free(snew);
                fclose(fp);
                return FAILURE;
            }

            strcpy(snew->file_name, token);

            /* Word count */
            token = strtok(NULL, ";");

            snew->word_count = atoi(token);

            snew->link = NULL;

            if (mnew->sublink == NULL)
            {
                mnew->sublink = snew;
                last = snew;
            }
            else
            {
                last->link = snew;
                last = snew;
            }
        }

        /* Insert Main Node into Hash Table */
        if (ht->table[index] == NULL)
        {
            ht->table[index] = mnew;
        }
        else
        {
            mainnode *temp = ht->table[index];

            while (temp->link != NULL)
            {
                temp = temp->link;
            }

            temp->link = mnew;
        }
    }

    fclose(fp);

    return SUCCESS;
}