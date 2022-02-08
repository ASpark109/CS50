// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Data structure root declaration
node *root;

//Pointer to the data structure for tree traversal
node *crawler;


node *temp[45];
int f = 0;

//The number of words written in the dictionary
unsigned int wordN = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialization of the tree root
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }

    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    
    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        crawler = root;
        int index = 0;
        for(int i = 0; word[i] != '\0'; i++)
        {
            //Determination of the index of the symbol
            //if the symbol is an apostrophe, the index is 26
            index = isalpha(word[i]) ? (word[i] - 'a') : 26;

            //The crawler moves on the pointer if it is not NULL
            if(crawler->children[index] != NULL)
            {
                crawler = crawler->children[index];
                
            }
            //If the pointer is NULL
            else
            {
                //Allocating memory for a new node
                crawler->children[index] = malloc(sizeof(node));
                crawler = crawler->children[index];

                //Initialization of a new node
                crawler->is_word = false;
                for (int q = 0; q < N; q++)
                {
                    crawler->children[q] = NULL;
                }
            }
        }

        //Announce the end of the added word
        crawler->is_word = true;
        wordN++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordN;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    crawler = root;
    int index = 0;

    for(int a = 0; a < strlen(word); a++)
    {
        //Determination of the index of the symbol
        //if the symbol is an apostrophe, the index is 26
        index = isalpha(word[a]) ? (tolower(word[a]) - 'a') : 26;

        //If the next character exists in the tree
        if(crawler->children[index] != NULL)
        {
            crawler = crawler->children[index];
        }
        else
        {
            crawler = root;
            return false;
        }
    }

    //If the end-of-word flag is true
    if(crawler->is_word == true)
    {
        crawler = root;
        return true;
    }
    //If the end-of-word flag is false
    else
    {
        crawler = root;
        return false;
    }
    
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        if(crawler->children[i] != NULL)
        {
            //Storage of the current address of the location of the crawler
            temp[f++] = crawler;

            //Go to the next node
            crawler = crawler->children[i];
            unload();
            
            //Go to the address of the previous node
            crawler = temp[--f];
        }
    }

    //free node memory
    free(crawler);
    return true;
}