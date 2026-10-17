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
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Count dictionary words
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int bucket_index = hash(word);
    node *current_node = table[bucket_index];

    while (current_node != NULL)
    {
        if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }
        current_node = current_node->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory
bool load(const char *dictionary)
{
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dictionary_file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(dictionary_file);
            unload();
            return false;
        }

        strcpy(new_node->word, word);

        unsigned int bucket_index = hash(word);

        new_node->next = table[bucket_index];
        table[bucket_index] = new_node;
        word_count++;
    }
    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node *current_node = table[i];
        while (current_node != NULL)
        {
            node *temporary_node = current_node;
            current_node = current_node->next;
            free(temporary_node);
        }
        table[i] = NULL;
    }
    word_count = 0;
    return true;
}


