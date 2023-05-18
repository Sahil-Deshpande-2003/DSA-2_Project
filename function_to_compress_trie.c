/*

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
        if (node->children[i] != NULL) {
            if (childCount > 1) {
            // Node has more than one child, skip compression
            return;
        }

        else if (childCount == 1) {

                printf("I am here\n");
            // Node has only one child, compress the node
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i] != NULL) {
                    child = node->children[i];
                    break;
                }
            }

            // Copy data from the child to the parent node
            strncpy(node->data, child->data, MAX_WORD_LENGTH);

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
}
}



*/