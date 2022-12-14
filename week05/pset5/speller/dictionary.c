// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Amount of words in my dictionary
int size_loaded = 0;

// Buckets where i store the linked lists
node *bucket[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int key = hash(word);

    for (node *actual_node = bucket[key]; actual_node != NULL; actual_node = actual_node->next)
    {
        if (strcasecmp(word, actual_node->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int key = toupper(word[0]) - 'A';
    if (word[1] != '\0')
    {
        if (word[1] == '\'')
        {
            key = (key + 1) * 27;
            key += 26;
        }
        else
        {
            key = (key + 1) * 27;
            key += toupper(word[1]) - 'A';
        }
    }
    return key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        bucket[i] = NULL;
    }

    char buffer[LENGTH + 1];
    while (fscanf(dict, "%s", buffer) != EOF)
    {
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            return false;
        }

        strcpy(tmp->word, buffer);
        
        unsigned int key = hash(tmp->word);

        if (bucket[key] == NULL)
        {
            tmp->next = NULL;
            bucket[key] = tmp;
        }
        else
        {
            tmp->next = bucket[key];
            bucket[key] = tmp;
        }
        size_loaded++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (size_loaded == 0)
    {
        return 0;
    }
    return size_loaded;
}

void unloadLinkedList(node *actual_node)
{
    if (actual_node == NULL)
    {
        return;
    }

    unloadLinkedList(actual_node->next);

    free(actual_node);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        unloadLinkedList(bucket[i]);
    }

    return true;
}
