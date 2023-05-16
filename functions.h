#include"Trie.h"
void compress(TrieNode *node);
void printCompressedTrie(TrieNode *node, char *prefix) ;
void initTrieNode(TrieNode *node, char letter);
bool search(TrieNode *root, char *word);
void insertWord(TrieNode *root, char *word);
void removeWord(TrieNode *root, char *word);
void destroyTrie(TrieNode* node);
TrieNode* createNode();
void display_trie(TrieNode* root, char* buffer, int depth) ;