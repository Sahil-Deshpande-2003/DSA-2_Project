#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>

#include<stdbool.h>

// SIZE IS AN ISSUE!!!!!

#define size 26

#define MAX_WORD_LENGTH 100

// This is my main file

typedef struct TrieNode{

    char data[1000];

    int index;

    bool isTerminal;

    struct TrieNode ** children;

}TrieNode;

TrieNode* init(){

    TrieNode *t = (TrieNode*)malloc(sizeof(TrieNode));


     t->index = 0;

    t->data[t->index] = '\0';


    t->isTerminal = false;

    t->children = (TrieNode**)malloc((sizeof(TrieNode*))*size);

    for (int i = 0; i < size; i++)
    {
        t->children[i] = NULL;
        /* code */
    }



    return t;
    
}

void insert_helper(TrieNode *root, char *key, int i){

    if (i == strlen(key)){

        root->isTerminal = true;

        return;

    }

    int ind = key[i] - 'a';

    TrieNode* child;

    if (root->children[ind]!=NULL){

        child = root->children[ind];

    }

    else{

        child = init();

        child->data[child->index] = key[i];

        child->index++;

        child->data[child->index] = '\0';

        root->children[ind] = child;
    }

    insert_helper(child,key,i+1);

    return;


}

void insert(TrieNode *t, char *key){

    insert_helper(t,key,0);

    return;

}

// not the compressed version!

void print_trie_helper(TrieNode* root, char* store, int ind) {
    if (root->isTerminal) {
        store[ind] = '\0';
        printf("%s\n", store);
        return;
    }
    for (int i = 0; i < size; i++) {
        if (root->children[i] != NULL) {
            store[ind] = 'a' + i;
            print_trie_helper(root->children[i], store, ind + 1);
        }
    }
    return;
}   



void print_trie(TrieNode*t){

    char store[200];

    print_trie_helper(t,store,0);

    return;

}

void compress_trie(TrieNode *root){



    if (!root) return;

    for (int i = 0; i < size; i++)
    {
          compress_trie(root->children[i]);

    

      
        /* code */
    }


    int childCount = 0;
    TrieNode*child = NULL;

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            childCount++;

            child = root->children[i];

            if (childCount>1) return;
        }


        /* code */
    }

    if (childCount == 1){

        // copy the data of child into parent

        // printf("Before compression\n");

        // printf("root = %s\n",root->data);

        // printf("child = %s\n",child->data);

        for (int i = 0; i < child->index; i++)
        {

            root->data[root->index++] = child->data[i];

            /* code */
        }

        root->data[root->index] = '\0';

        root->isTerminal  = child->isTerminal;

        for (int i = 0; i < size; i++)
        {

            root->children[i] = child->children[i];


            /* code */
        }

        free(child);


        //  printf("After compression\n");


        //  printf("root = %s\n",root->data);

        
        


    }

    return ;

    
    
    
}

// void display_compress_trie(TrieNode t){

//     for (int i = 0; i < size; i++)
//     {
//         if (t.children[i]) printf("%s\n",t.children[i]->data);
//         /* code */
//     }

//     return;
    
// }

void auto_complete_helper(TrieNode *root, int i, char *key,char* buffer, int depth){

    // base case

    // printf("root = %s\n",root->data);


    if (i == strlen(key)){

        // printf("Inside base case, root = %s\n",root->data);
        

        for (int i = 0; i < size; i++)
        {
            if (root->children[i] && root->children[i]->isTerminal){

                //printf("char_final = %c\n",'a'+i);
                
                 buffer[depth++] = 'a' + i;

                 buffer[depth] = '\0';

                printf("%s\n", buffer);

                depth--;
                 
            }
            
            /* code */
        }
        


      


        return;

    }

    // printf("Hi?\n");


    int ind = key[i] - 'a';

    // printf("ind = %d\n",ind);

    TrieNode* child;

    // printf("Printing child array of root\n");

    // for (int i = 0; i < size; i++)
    // {
    //     if (root->children[i]) printf("child = %s\n",root->children[i]->data);
    //     /* code */
    // }
    

    if (root->children[ind]!=NULL){

        // printf("root = %s\n",root->data);


        child = root->children[ind];

        buffer[depth] = 'a' + ind;

        // printf("char_insert = %c\n",'a'+i);

        auto_complete_helper(child,i+1,key,buffer,depth+1);
    }



    //   printf("**************************\n");

    return;



}

void auto_complete_new(TrieNode *root, char *key,char* buffer, int depth){

    if (!root) return;

    printf("key = %s\n",key);

    printf("Printing child array\n");

    return;

    for (int i = 0; i < size; i++)
    {


        if (root->children[i]) printf("%s\n",root->children[i]->data);
        /* code */
    }
    


    for (int i = 0; i < size; i++)
    {

        if (root->children[i]){

        buffer[depth++] = 'a' + i;

        if (!(root->children[i]->isTerminal)){

            auto_complete_new(root,key,buffer,depth+1);
        }

        else{

            buffer[depth] = '\0';

            printf("%s\n",buffer);

            depth--;

        }

        }

        


        /* code */
    }
    
    
    return;


}

void auto_complete_recursion_2nd_step(TrieNode *root,char *key,char* buffer, int *depth){

    // base case

    if (!root) return;

   

    TrieNode*child;

    // printf("***************************************************\n");

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            //  printf("root = %s\n",root->data);

            child = root->children[i];

            // printf("child = %s\n",child->data);

            // printf("buffer = %s\n",buffer);

            // printf("depth = %d\n",*depth);


            buffer[(*depth)++] = 'a' + i; // yaha seg fault aa raha hai,depth is taking garbage value

            

            // printf("Dead\n");

            if (child->isTerminal){

                // printf("Inside is Terminal\n");

                // printf("When I just entered, depth = %d\n",(*depth));

                buffer[(*depth)] = '\0';

                printf("%s\n",buffer);

                //  printf("Just before decrementing, depth = %d\n",(*depth)); // fine

                // printf("After buffer\n");

                (*depth)--; // this was the error   *(depth)-- lol

                // printf("Before leaving, depth = %d\n",(*depth));

                // auto_complete_recursion_2nd_step(child,key,buffer,depth);

                
            }

            else auto_complete_recursion_2nd_step(child,key,buffer,depth);

            //printf("Here?\n");
            

        }





    }

    (*depth)--;
    
    return;

}

// working

TrieNode* auto_complete_iteration_1st_step(TrieNode *root,char *key,char* buffer, int *depth){

    if (!root) return root;

    int j = 0;

    while(j<strlen(key)){

        int ind = key[j] - 'a';

        if (root->children[ind]){

            root = root->children[ind];

            buffer[(*depth)++] = key[j];

        }

        j++;

    }

    buffer[(*depth)] = '\0';

    return root;

        

}

void auto_complete(TrieNode *root,char *key){

    // updates the root as well as buffer, after this function is executed 
    // key contains just 1 char and root is updated

    char buffer[MAX_WORD_LENGTH];

    int depth = 0;

    TrieNode*first = auto_complete_iteration_1st_step(root,key,buffer,&depth);

    

    // printf("new root = %s\n",first->data);

    // printf("new buff = %s\n",buffer);

    // printf("new depth = %d\n",depth);

    auto_complete_recursion_2nd_step(first,key,buffer,&depth);

    
  

    return;
}

void display_trie(TrieNode* root, char* buffer, int depth) {
    if (root->isTerminal) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < size; i++) {
        if (root->children[i] != NULL) {
            buffer[depth] = 'a' + i;
            display_trie(root->children[i], buffer, depth + 1);
        }
    }
}










int main(){


    TrieNode*t = init();
    // insert(t,"adgqs");
    // insert(t,"adgqr");
    // insert(t,"aez");
    // insert(t,"aeo");
    // insert(t,"afm");
    // insert(t,"bn");
    // insert(t,"cp");

    insert(t,"abandon");
    insert(t,"are");
    insert(t,"assessment");
    insert(t,"assistance");
    insert(t,"boo");
    insert(t,"boorish");
    insert(t,"brave");
    
   char buffer[MAX_WORD_LENGTH];
    // display_trie(t, buffer, 0);
    // compress_trie(t);

    display_trie(t,buffer,0); // working

    printf("\n\n\n");

    auto_complete(t,"b"); // not working
  

    


    




















    return 0;
}