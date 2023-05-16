#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"
#include"functions.h"
#define MAX_WORD_LENGTH 2000

int main() {
    // Create a new root node
    TrieNode* root = createNode();

    // Insert some words into the Trie
    insertWord(root, "apple");
    insertWord(root, "banana");
    insertWord(root, "orange");
    insertWord(root, "pear");
    insertWord(root, "peach");
    insertWord(root, "apricot");
    insertWord(root, "avocado");
    insertWord(root, "sahil");
    insertWord(root, "manas");

    

    char buffer[MAX_WORD_LENGTH];
    display_trie(root, buffer, 0);


    // Compress the Trie
    //compress(root);

    // Print the compressed Trie
    //printf("Compressed Trie:\n");
    //printCompressedTrie(root, 0);

    // Free the memory used by the Trie
    //destroyTrie(root);

    return 0;
}
