/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


// craetes root node
node * root = NULL;

// variable for counting words in loaded dictionary
unsigned int counter = 0;

// indicator of successful loading
bool loaded = false;

// function to get index [0-26] for char
int get_idx(char character)
{
    int index = character - 97;
    if (character == '\'')
        index = 26;
    return index;
}

// function to free nodes with recursion
void free_nodes(node * cursor)
{
    for (int i = 0; i<27; i++)
    {
        if (cursor->children[i] != NULL)
        {
            free_nodes(cursor->children[i]);
        }
    }
    free(cursor);
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // length of input word
    int word_len = strlen(word);

    // not "const" copy of word
    char word_copy[word_len];

    // filling word_copy and lowering letter
    for (int i = 0; i < word_len; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    // new node to keep root unchanged
    node * root_copy = root;

    // iterates over letters in word
    for (int i = 0; i < word_len; i++)
    {
        // get index of node in children
        int index = get_idx(word_copy[i]);

        // if word not in dictionary
        if (root_copy->children[index] == NULL)
        {
            return false;
        }

        // go to next node of word
        root_copy = root_copy->children[index];
    }

    // if word in dictionary - return true, else - false
    return root_copy->is_word;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // creates root node
    root = malloc(sizeof(node));

    // error checking
    if (root == NULL)
    {
        return false;
    }

    // sets all variables in node to initial values
    for (int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    root->is_word = false;

    // opens dictionary file for reading
    FILE * file = fopen(dictionary, "r");

    // error checking
    if (file == NULL)
    {
        return false;
    }

    // loop for reading from file
    while (1)
    {
        char word[LENGTH + 1];

        // reads one word and puts it to "word"
        fscanf(file, "%s", word);

        int word_len = strlen(word);

        // stops process if OEF reached
        if (feof(file))
        {
            break;
        }

        // new node to keep root unchanged
        node * root_copy = root;

        // iterates over letters in word
        for (int i = 0; i < word_len; i++)
        {
            // index of node
            int index = get_idx(word[i]);

            // creates node if it doesn't exist yet
            if (root_copy->children[index] == NULL)
            {
                node * new_node = malloc(sizeof(node));

                // error checking
                if (root == NULL)
                {
                    return false;
                }

                // sets all variables in node to initial values
                for (int i = 0; i < 27; i++)
                {
                    new_node->children[i] = NULL;
                }
                new_node->is_word = false;

                // inserts new node
                root_copy->children[index] = new_node;
            }
            // goes to the next node
            root_copy = root_copy->children[index];
        }
        // when end of word reached, sets is_word to true
        root_copy->is_word = true;
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
    // uses recursion function to free all nodes
    free_nodes(root);
    return true;
}
