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

// Represents a trie
node *root;

int count = 0;

int get_index(char c)
{
    int code = (int) c;

    if (code == 39)
    {
        return N - 1;
    }

    return tolower(c) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
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
        // TODO
        node *curr = root;
        count++;

        for (int i = 0, l = strlen(word); i < l; i++)
        {
            int index = get_index(word[i]);

            if (curr->children[index] == NULL)
            {
                node *new_node = malloc(sizeof(node));

                if (new_node == NULL)
                {
                    return 1;
                }

                new_node->is_word = false;

                for (int j = 0; j < N; j++)
                {
                    new_node->children[j] = NULL;
                }

                curr->children[index] = new_node;
            }

            curr = curr->children[index];
        }

        curr->is_word = true;
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
    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *curr = root;

    for (int i = 0, l = strlen(word); i < l; i++)
    {
        int index = get_index(word[i]);

        if (!curr->children[index])
        {
             return false;
        }

        curr = curr->children[index];
    }

    return curr->is_word;
}

bool free_node(node *node)
{
    for (int i = 0; i < N; i++)
    {
        if (node->children[i])
        {
            free_node(node->children[i]);
        }
    }

    free(node);

    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return free_node(root);
}
