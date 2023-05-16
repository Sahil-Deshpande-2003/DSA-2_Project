#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    char letter;
    bool isTerminal;
    struct TrieNode *children[ALPHABET_SIZE];
} TrieNode;

typedef struct Trie {
    TrieNode* root;
} Trie;


#endif /* TRIE_H */
