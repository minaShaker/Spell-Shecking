/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H

//struct for saving dictionary in
typedef struct node {
    char c;
    struct node * peer;
    struct node * child;
    bool b;
}node;

//makes 1 word inside the memory
node * makeWord(char * word ,node ** nodePP );



//free memory
node * RecursiveUnload(node * nodeU);

void search (char * word);

extern node * node1;
extern unsigned int number ;