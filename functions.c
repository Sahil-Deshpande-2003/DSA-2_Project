#include <stdlib.h>
#include <string.h>
#include "Trie.h"
#include"functions.h"
// Creates a new TrieNode
TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isTerminal = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Recursively frees all nodes in the Trie
void destroyTrie(TrieNode* node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        destroyTrie(node->children[i]);
    }
    free(node);
}


void initTrieNode(TrieNode *node, char letter) {
    node->letter = letter;
    node->isTerminal = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
}

bool search(TrieNode *root, char *word) {
    if (*word == '\0') {
        return root->isTerminal;
    }

    int index = *word - 'a';
    TrieNode *child = root->children[index];

    if (child == NULL) {
        return false;
    }

    return search(child, word + 1);
}

void insertWord(TrieNode *root, char *word) {
    if (*word == '\0') {
        root->isTerminal = true;
        return;
    }

    int index = *word - 'a';
    TrieNode *child = root->children[index];

    if (child == NULL) {
        child = malloc(sizeof(TrieNode));
        initTrieNode(child, *word);
        root->children[index] = child;
    }

    insertWord(child, word + 1);
}

void removeWord(TrieNode *root, char *word) {
    if (*word == '\0') {
        root->isTerminal = false;
        return;
    }

    int index = *word - 'a';
    TrieNode *child = root->children[index];

    if (child == NULL) {
        return;
    }

    removeWord(child, word + 1);

    if (!child->isTerminal) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (child->children[i] != NULL) {
                return;
            }
        }

        free(child);
        root->children[index] = NULL;
    }
}
