/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//make a gloabal pointer to point to the first node
node * node1;

/**
 * Returns true if word is in dictionary else false.
 */
unsigned int number =0 ;
bool check(const char *word)
{
    // allocate memory for a conatainer for the word
    char * word2 = (char*)malloc((strlen(word)+1)*(sizeof(char)));

    //copy from word to word2 and change it to lower case
    for(int x =0 ,n = strlen(word)+1;x<n;x++)
    {
        word2[x] =word[x];
        if (isalpha(word[x]))
            word2[x]=tolower(word2[x]);
    }

    //create dublicate to node1 (the fisrst pointer)
    node * nodeC ;
    nodeC = node1;

    // iterate over each letter
    for (int x =0 , n = strlen(word2) ; x<n ; x++)
    {
        //repeat untill either we find the letter (word[x])
        //or we can't find it if we reached NULL and return 0
        while (!( nodeC->c == word2[x] ))
        {

            //check if we reached NULL
            if (nodeC->peer == NULL )
            {
                free(word2);
                return 0;
            }

            //move to the next peer
            else
                nodeC = nodeC-> peer;
        }

        //move to it's children to start to test it for the next loop unless it's the last loop and this is the last letter
        if (x!=n-1 )
            nodeC=nodeC->child;
        if (nodeC == NULL)
        {
            free(word2);
            return 0;
        }
    }
    free(word2);

    //check if the b in the node id true or not
    return nodeC->b;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // container for the word
    char word[LENGTH+1] ;

    //opening the dictionary to read it
    FILE * dictionaryF = fopen(dictionary, "r" );

    fscanf(dictionaryF,"%s",word);

    //making the first word
    makeWord( word,&node1 );
    //iterating over each word
    while ( fscanf(dictionaryF,"%s",word) != EOF )
    {
        search(word);
    }

    fclose(dictionaryF);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //the number counter is in the makeWord() base case;
    return number;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{

    if (RecursiveUnload(node1)== NULL)
        return 1;
    else
        return 0;
}

// load a word in the system ,takes the word and a pointer to pointer to the node in which it gonna attatch it to and then return it's pointer
//if there is no node to attatch the word to send NULL and it will make new link list with the word and return it
node * makeWord(char * word ,node ** nodePP  )
{
    // makeWord(); iteratively
    /*
    int x =0;
    node* nodeMW ;
    while (!(word[x]== '\0'))
    {
        nodeMW = malloc(sizeof(node));
        *nodePP = nodeMW;
        nodePP=&(nodeMW->child);
        nodeMW->c = word[x];
        nodeMW->child=NULL;
        nodeMW->peer=NULL;
        if (word[x+1]=='\0')
        {
            nodeMW -> b =1;
            number++;
        }else{
            nodeMW->b=0;
        }
        x++;

    }*/

    //make word recursivley
    node *nodeMW = malloc(sizeof(node));

    //check if we still have enough memory
    if (nodeMW == NULL)
    {
        printf("No enough space for dictionary\n\nExitting....\n");
        exit(0);
    }

    //if the user send a pointer to attatch it to the word, make this pointer equals to the new allocated node
    if (nodePP != NULL)
        *nodePP = nodeMW;

    //base case if we reached the last letter
    if (word[1] == '\0' )
    {
        nodeMW -> c = word[0];
        nodeMW -> peer = NULL;
        nodeMW -> child =NULL;

        //as a key for us to check if this a valid word
        nodeMW -> b = 1;

        //counter for size();
        number ++;
        return nodeMW;

    //recursion case if we still didn't reach the last letter
    }else{
        nodeMW -> c = word[0];
        nodeMW -> peer = NULL;
        nodeMW -> b = 0;

        //send pointer to pointer to child to attatch the rest of the word to it
        makeWord(word+1,&(nodeMW->child));
        return nodeMW;
    }
}


//free the memory
node * RecursiveUnload(node * nodeU)
{
    //base case if we reached the end free it and retrun NULL
    if (nodeU-> peer ==NULL && nodeU-> child == NULL)
    {
        free(nodeU);
        return NULL;
    }
    else

        //first if it has peers free them
        if (nodeU->peer != NULL)
            nodeU -> peer = RecursiveUnload(nodeU->peer);

        //second if it has children free them
        if (nodeU->child != NULL)
            nodeU-> child = RecursiveUnload(nodeU->child);

        //finally free the node itself
        return RecursiveUnload(nodeU);
}

/*
 *for finding if there is similarity between the word we want to add and the words in the dictionary so we won't need to add new
 *words every time
*/
void search (char * word)
{
    //create dublicate to node1 (the fisrst pointer)
    node * nodeS ;
    nodeS = node1;

    //to know how many letters of the word we can skip
    int x =0;

    //to point to the node pointer we want to attatch the rest of the word to
    node ** nodePP= NULL;

    // iterate over each letter

    //repeat untill either we find the letter (word[x]) and we break to find the next letter
    //or we can't find it if we reached NULL and return the pointer
    while ( 1 )
    {

        //check if we found word[x] so we go on to it's children for the next letter and break
        if (nodeS-> c == word[x])
        {

            //if we reached the end of the children end
            if (nodeS->child == NULL )
            {
                //we already found this letter word[x] so we should skip it
                x++;
                nodePP = &(nodeS->child);
                goto z;
                //here nodeS is the node that we should add to it's  children
            }

            nodeS = nodeS->child;
            x++;
        }

        //check if we reached NULL
        else if (nodeS ->peer == NULL )
        {
            nodePP = &(nodeS->peer);
            goto z;
            //here nodeS is the node that we should add to it's peer
        }

        //check the next peer
        else
            nodeS =nodeS-> peer;
    }

    //send the word to be added and pointer to pointer to node in which we want to attatch the word
    z :makeWord( word+x , nodePP );
}