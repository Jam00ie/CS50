// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 200000;
char curr_word[LENGTH + 1];
int dict_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int key = hash(word);
    node *cursor = table[key];
    while (cursor->next != NULL)
    {
        if (strcasecmp(word, (cursor->next)->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        table[i]->next = NULL;
    }

    // Opens dictionary file
    FILE *infile = fopen(dictionary, "r");
    if (!infile)
    {
        printf("Error opening file!\n");
        return false;
    }

    // Reads from file
    while (fscanf(infile, "%s", curr_word) == 1)
    {
        // initialize word node
        node *cursor = malloc(sizeof(node)); // assign memory to cursor *
        strcpy(cursor->word, curr_word);     // copy the word onto word node

        unsigned int key = hash(curr_word);
        cursor->next = table[key]->next;
        table[key]->next = cursor;
        dict_size++;
    }

    // close dictionary file
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

void empty_branch(node *current)
{
    if (current->next != NULL)
    {
        empty_branch(current->next);
    }
    free(current);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        empty_branch(table[i]);
    }
    return true;
}
