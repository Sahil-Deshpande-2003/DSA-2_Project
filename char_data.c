#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 100

// insert and remove are working 

typedef struct TrieNode {
    char data[MAX_WORD_LENGTH];
    struct TrieNode* children[ALPHABET_SIZE];
    int isTerminal;
} TrieNode;

TrieNode* createNode(const char* data) {
    TrieNode* newNode = (TrieNode*) malloc(sizeof(TrieNode));
    strncpy(newNode->data, data, MAX_WORD_LENGTH);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    newNode->isTerminal = 0;
    return newNode;
}

void insertWord(TrieNode* root, const char* word) {
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
        child = createNode(word);
        root->children[index] = child;
    }

    // Recursive call
    insertWord(child, word + 1);
}

int search(TrieNode* root, const char* word) {
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

void removeWord(TrieNode* root, const char* word) {
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

void displayTrie(TrieNode* node) {
if (node == NULL) {
return;
}

printf("Data: %s\n", node->data);

printf("\n\n");

// Recursively display children
for (int i = 0; i < ALPHABET_SIZE; i++) {
    displayTrie(node->children[i]);
}

}


void compressTrie(TrieNode* node) {
    // Base case
    if (node == NULL) {
        return;
    }



    // Recursively compress children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        compressTrie(node->children[i]);
    }

    // Check if the node has only one child
    int childCount = 0;
    TrieNode* child = NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
       
       if (node->children[i]){

        childCount++;

        if (childCount>1) return;

        child = node->children[i];

        

        

       }


    }

    if (childCount == 1){


        printf("node_start = %s\n",node->data);

        printf("child = %s\n",child->data);




         // Copy data from the child to the parent node
            strncpy(node->data, child->data, MAX_WORD_LENGTH);
            
            printf("node_final = %s\n",node->data);

            // Set the parent node as terminal if the child is terminal
            node->isTerminal = child->isTerminal;

            // Copy children of the child node to the parent node
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                node->children[i] = child->children[i];
            }


            // Free the memory of the child node
            free(child);

    }
}

void displayCompressedTrie(TrieNode* node) {
    if (node == NULL) {
        return;
    }

    printf("Data: %s\n", node->data);

    printf("\n\n");

    // Recursively display children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            displayCompressedTrie(node->children[i]);
        }
    }
}

int main() {
    TrieNode* root = createNode("");
    insertWord(root, "hello");
    compressTrie(root);
    free(root);
    return 0;
}
