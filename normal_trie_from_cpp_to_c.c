

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    char data;
    struct TrieNode* children[ALPHABET_SIZE];
    int isTerminal;
} TrieNode;

TrieNode* createNode(char data) {
    TrieNode* newNode = (TrieNode*) malloc(sizeof(TrieNode));
    newNode->data = data;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    newNode->isTerminal = 0;
    return newNode;
}

void insertWord(TrieNode* root, char* word) {
    // Base case
    if (*word == '\0') {
        root->isTerminal = 1;
        return;
    }

    // Small Calculation
    int index = *word - 'a';
    TrieNode* child;
    if (root->children[index] != NULL) {
        child = root->children[index];
    } else {
        child = createNode(*word);
        root->children[index] = child;
    }

    // Recursive call
    insertWord(child, word + 1);
}

int search(TrieNode* root, char* word) {
    if (*word == '\0') {
        return root->isTerminal;
    }

    // Small Calculation
    int index = *word - 'a';
    TrieNode* child;
    if (root->children[index] != NULL) {
        child = root->children[index];
    } else {
        return 0;
    }

    // Recursive call
    return search(child, word + 1);
}

void removeWord(TrieNode* root, char* word) {
    // Base case
    if (*word == '\0') {
        root->isTerminal = 0;
        return;
    }

    // Small calculation
    TrieNode* child;
    int index = *word - 'a';
    if (root->children[index] != NULL) {
        child = root->children[index];
    } else {
        // Word not found
        return;
    }

    removeWord(child, word + 1);

    // Remove child Node if it is useless
    if (child->isTerminal == 0) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (child->children[i] != NULL) {
                // it means a child exists for this child so do noting just return
                return;
            }
        }

        // reached here means that no child exists for that child plus it's not terminal
        // so it is useless node and so just delete this child

        free(child);
        root->children[index] = NULL;
    }
}

int main() {
    TrieNode* root = createNode('\0');
    insertWord(root, "hello");
    insertWord(root, "world");
    printf("%d\n", search(root, "hello")); // 1
    printf("%d\n", search(root, "world")); // 1
    printf("%d\n", search(root, "hell")); // 0
    removeWord(root, "hello");
    printf("%d\n", search(root, "hello")); // 0
    printf("%d\n", search(root, "world")); // 1
    free(root);
    return 0;
}