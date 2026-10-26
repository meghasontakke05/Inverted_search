#include "inverted_search.h"

int hash_function(char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return 26;
    }

    if (word[0] >= 'a' && word[0] <= 'z')
    {
        return word[0] - 'a';
    }
    else if (word[0] >= 'A' && word[0] <= 'Z')
    {
        return word[0] - 'A';
    }
    else
    {
        return 26;
    }
}