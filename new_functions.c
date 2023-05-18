#include<stdio.h>
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

// Compresses a Trie by merging parent nodes with single children
void compress(TrieNode *node) {
    if (node == NULL) {
        return;
    }

    // Recursively compress children first
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        compress(node->children[i]);
    }

    // Merge parent with single child
    int num_children = 0;
    int child_index = -1;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            num_children++;
            child_index = i;
        }
    }

    if (num_children == 1) {
        TrieNode *child = node->children[child_index];
        node->letter = child->letter;
        node->isTerminal = child->isTerminal;
        memcpy(node->children, child->children, ALPHABET_SIZE * sizeof(TrieNode*));
        free(child);
    }
}

// Prints the Trie in a compressed format
void printCompressedTrie(TrieNode *node, char *prefix) {
    if (node == NULL) {
        return;
    }

    // Print the prefix and letter if it's a terminal node
    if (node->isTerminal) {
        printf("%s%c\n", prefix, node->letter);
    }

    // Recursively print compressed children
    int num_children = 0;
    int child_index = -1;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            num_children++;
            child_index = i;
        }
    }

    if (num_children == 1) {
        char new_prefix[strlen(prefix) + 1];
        sprintf(new_prefix, "%s%c", prefix, node->letter);
        printCompressedTrie(node->children[child_index], new_prefix);
    } else {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != NULL) {
                char new_prefix[strlen(prefix) + 1];
                sprintf(new_prefix, "%s%c", prefix, node->letter);
                printCompressedTrie(node->children[i], new_prefix);
            }
        }
    }
}

void display_trie(TrieNode* root, char* buffer, int depth) {
    if (root->isTerminal) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            display_trie(root->children[i], buffer, depth + 1);
        }
    }
}

void auto_complete(TrieNode *root, char *word){

    
    


}


