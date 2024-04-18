/*
Liam Hudson
COP 3502
April 18, 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26

// Trie structure
struct Trie
{	
    int count;
    struct Trie *children[ALPHABET];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *curr = pTrie;
    if (curr == NULL) {
        curr = (struct Trie *) malloc(sizeof(struct Trie));
        for (int i = 0; i < ALPHABET; i++)
            curr->children[i] = NULL;
        pTrie = curr;
    }
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = (struct Trie *) malloc(sizeof(struct Trie));
            for (int j = 0; j < ALPHABET; j++) {
                curr->children[index]->children[j] = NULL;
            }
        }
        curr = curr->children[index];
    }
    // Increment the count for the last node representing the word
    if (curr->count == 0) 
        curr->count = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *curr = pTrie;
    if (curr == NULL) {
        curr = (struct Trie *) malloc(sizeof(struct Trie));
        curr->count = 0;
        for (int i = 0; i < ALPHABET; i++)
            curr->children[i] = NULL;
        pTrie = curr;
    }
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = (struct Trie *) malloc(sizeof(struct Trie));
            curr->children[index]->count = 0;
            for (int j = 0; j < ALPHABET; j++) 
                curr->children[index]->children[j] = NULL;
        }
        curr = curr->children[index];
    }
    // Increment the count for the last node representing the word
    curr->count++;
    return curr->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET; i++) {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie(struct Trie *trie, int n)
{
    char word[101];
    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(trie, word);
    }
    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    struct Trie *trie = NULL;
    int n = 0;
    FILE *ifp;
    ifp = fopen(filename, "r");
    fscanf(ifp, "%d", &n);
    *pInWords = malloc(n*sizeof(char));
    if (*pInWords == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        pInWords[i] = malloc(101 * sizeof(char));
        fscanf(ifp, "%s", pInWords[i]);
    }
    fclose(ifp);
    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie(pTrie, numWords);
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}