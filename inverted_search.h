#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

#define HASH_SIZE 27      // 26 alphabets + 1 for special characters/numbers

/* File List */
typedef struct file_node
{
    char *file_name;

    struct file_node *link;
} filelist;

/* Sub Node */
typedef struct sub_node
{
    int word_count;
    char *file_name;
    struct sub_node *link;
} subnode;

/* Main Node */
typedef struct main_node
{
    char *word;
    int file_count;
    subnode *sublink;
    struct main_node *link;
} mainnode;

/* Hash Table */
typedef struct hash_table
{
    mainnode *table[HASH_SIZE];
} hashtable;

/* Function Prototypes */

/* Validation */
int validation(char *filename, filelist **head);



/* Hash Function */
int hash_function(char *word);

int create_database(hashtable *ht, filelist *head);
int is_file_present(hashtable *ht, char *filename);
int update_database(hashtable *ht, char *filename);
int display_database(hashtable *ht);
int save_database(hashtable *ht);
int search_database(hashtable *ht);



#endif