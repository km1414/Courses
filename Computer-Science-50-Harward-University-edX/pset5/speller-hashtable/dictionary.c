/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"


// craetes an array of nodes - hashtable
node * hashtable[SIZE] = {NULL};

// variable for counting words in loaded dictionary
unsigned int counter = 0;

// indicator f successful loading
bool loaded = false;

// hash function from Stroustrup's book. Returns predetermined int for every str.
int hash(char *str)
{
    unsigned int h = 0;
    while (*str)
       h = h << 1 ^ *str++;
    return (h > 0 ? h : -h) % SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // length of input word
    int word_len = strlen(word);

    // not "const" copy of word
    char word_copy[word_len + 1];

    // filling word_copy and lowering letter
    for (int i = 0; i < word_len; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    
    // end of string
    word_copy[word_len] = '\0';

    // number of bucket where word is stored
    int index = hash(word_copy);

    // cursor for linked-list
    node * cursor = hashtable[index];

    // checks if word is in linked-list, until end reached
    while (cursor != NULL)
    {
        // stops loop if word found
        if (strcmp (cursor->word, word_copy) == 0)
        {
            return true;
        }
        
        // goes to next node in linked-list if not found
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // opens dictionary file for reading
    FILE * file = fopen(dictionary, "r");

    // problems detection
    if (file == NULL)
    {
        return false;
    }

    // loop for reading from file
    while (1)
    {
        // new node for new word
        node * new_node = NULL;
        new_node = malloc(sizeof(node));

        // problems detection
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // reads one word and puts it to new_node
        fscanf(file, "%s", new_node->word);

        // stops process if OEF reached
        if (feof(file))
        {
            free(new_node);
            break;
        }

        // number of bucket for word to be stored
        int index = hash(new_node->word);

        // inserts new_node to the beginning of linked-list
        new_node->next = hashtable[index];
        hashtable[index] = new_node;
        counter++;
    }
    // great success
    fclose(file);
    loaded = true;
    return true;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (loaded)
    {
    return counter;
    }
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // cursor for linked-list
    node * cursor = NULL;

    // iterates over all buckets
    for (int i = 0; i < SIZE; i++)
    {
        cursor = hashtable[i];
        
        // iterates until last node
        while (cursor != 0)
        {
            // points to every node in linked-list and frees it
            node * temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
