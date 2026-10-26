#include "inverted_search.h"

int validation(char *filename, filelist **head)
{
    FILE *fp;
    char *ext;
    filelist *temp;

    /* Check file extension */
    ext = strrchr(filename, '.');

    if (ext == NULL || strcmp(ext, ".txt") != 0)
    {
        printf("ERROR : %s is not a .txt file\n", filename);
        return FAILURE;
    }

    /* Check file exists */
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("ERROR : %s file does not exist\n", filename);
        return FAILURE;
    }

    /* Check file is empty */
    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        printf("ERROR : %s is an empty file\n", filename);
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);

    /* Check duplicate file */
    temp = *head;

    while (temp != NULL)
    {
        if (strcmp(temp->file_name, filename) == 0)
        {
            printf("INFO : %s already exists in file list\n",filename);
            return FAILURE;
        }

        temp = temp->link;
    }

    /* Create new node */
    filelist *new = malloc(sizeof(filelist));

    if (new == NULL)
    {
        return FAILURE;
    }

    /* Allocate memory for filename */
    new->file_name = malloc(strlen(filename) + 1);

    if (new->file_name == NULL)
    {
        free(new);
        return FAILURE;
    }

    strcpy(new->file_name, filename);
    new->link = NULL;

    /* Insert into linked list */
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        temp = *head;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new;
    }

    return SUCCESS;
}