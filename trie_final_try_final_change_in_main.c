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

void print_buffer(char *buffer, int depth){

    buffer[depth] = '\0';

    printf("%s\n",buffer);

    depth--;

    return;

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

void display_compress_trie(TrieNode *t,char *buffer, int depth){



    if (!t){



        return;
    }


    TrieNode *child;


    for (int i = 0; i < size; i++)
    {

        
        if (t->children[i]){
            

            child = t->children[i];

            int j = 0;

            while (j<child->index)
            {

        
                buffer[depth++] = child->data[j];

                j++;
                
                /* code */
            }


            if(child->isTerminal){


                buffer[depth] = '\0';


                printf("%s\n",buffer);
                
            }


            display_compress_trie(child,buffer,depth);

             for (int i = 0; i < child->index; i++)
                {
                    depth--;
                    /* code */
                }
            
        }

        /* code */
    }
    
    return;
}



TrieNode* compress_trie(TrieNode *root){

    // printf("root = %s\n",root->data);

    if (!root) return root;
    
    TrieNode*child = NULL;

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            // printf("root = %s\n",root->data);


            child = root->children[i];

            // printf("child before functional call = %s\n",child->data);

            child =  compress_trie(child);

            // printf("root = %s\n",root->data);

            // printf("child after functional call = %s\n",child->data);

            // printf("buffer = %s\n",buffer);

            // printf("child == buffer = %d\n",strcmp(child->data,buffer));


            root->children[i] = child;

            
            if (root->data[0] == '\0'){

                // printf("I am here\n");

                return root;
            }

        }
         

    
    }

    int childCount = 0;

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            childCount++;

            child = root->children[i];

            if (childCount>1) return root;
        }


    }

    if (childCount == 1){


        for (int i = 0; i < child->index; i++)
        {

            root->data[root->index++] = child->data[i];

        }

        root->data[root->index] = '\0';

        root->isTerminal  = child->isTerminal;

        for (int i = 0; i < size; i++)
        {

            root->children[i] = child->children[i];
        }

        free(child);

        
    }

    return root ;

    
    
    
}


void auto_complete_2nd_step_compressed_version(TrieNode *t,char *buffer, int depth){



    if (!t){


        return;
    }

    // printf("Inside recursive function, root = %s\n",t->data);
    

    if (t->isTerminal){

        // printf("root is terminal\n");

        buffer[depth] = '\0'; // reset required?

    printf("%s\n",buffer);        

    }

    TrieNode *child;


    for (int i = 0; i < size; i++)
    {

        
        if (t->children[i]){
            


            child = t->children[i];

            int j = 0;

            while (j<child->index)
            {

                buffer[depth++] = child->data[j];

                j++;
                
            }


            // if(child->isTerminal){

            //     // printf("Inside child?\n");

            //     printf("root inside child is Terminal = %s\n",t->data);


            //     buffer[depth] = '\0';

            //     printf("%s\n",buffer);
                
            // }


            auto_complete_2nd_step_compressed_version(child,buffer,depth);

             for (int i = 0; i < child->index; i++)
                {
                    depth--;

                }
            
        }


    }
    
    return;
}










void auto_complete_recursion_2nd_step(TrieNode *root,char *key,char* buffer, int *depth){



    if (!root) return;

    TrieNode*child;

    if (root->isTerminal) {

        printf("root = %s\n",root->data);

        
        printf("%s\n",buffer);
    }

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){



            child = root->children[i];


            buffer[(*depth)++] = 'a' + i; // yaha seg fault aa raha hai,depth is taking garbage value

            

            if (child->isTerminal){


                buffer[(*depth)] = '\0';

                printf("%s\n",buffer);

                auto_complete_recursion_2nd_step(child,key,buffer,depth);

                //(*depth)--; // this was the error   *(depth)-- lol
                              
            }

            else auto_complete_recursion_2nd_step(child,key,buffer,depth);

            

        }


    }

    (*depth)--;
    
    return;

}



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
    

    auto_complete_recursion_2nd_step(first,key,buffer,&depth);

    
  

    return;
}

TrieNode* auto_complete_iteration_1st_step_compressed_version(TrieNode *root,char *key, char *buffer, int *depth){

     if (!root) return root;

    int j = 0;

    while(j<strlen(key)){

        int ind = key[j] - 'a';

        if (root->children[ind]){

            //printf("I am here\n");

            root = root->children[ind];


            int m = 0;

            while(m<root->index){

                buffer[(*depth)++] = root->data[m++];
            }

        }

        // else{

        //     printf("Not found\n");

        //     return NULL;
        // }

        j++;

    }

    buffer[(*depth)] = '\0';

    return root;


}


void auto_complete_compressed_version(TrieNode *root,char *key){

    // updates the root as well as buffer, after this function is executed 
    // key contains just 1 char and root is updated

    char buffer[MAX_WORD_LENGTH];

    int depth = 0;

    TrieNode*first = auto_complete_iteration_1st_step_compressed_version(root,key,buffer,&depth);


    if ((!first) || first->data[0] == '\0') {

        // printf("Inside new if tion\n");

        return;
    }

      

        
    

    // printf("first = %s\n",first->data);
 

    auto_complete_2nd_step_compressed_version(first,buffer,depth);

    
  

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

int count_nodes(TrieNode *t){

    if (!t) return 0;

    int ct = 0;


    for (int i = 0; i < size; i++)
    {
        if (t->children[i]) ct+=count_nodes(t->children[i]);
        /* code */
    }

    return 1+ct;


    

}








int main(){

//    FILE *fp;
    TrieNode *t = init();

    char *filename = "new.txt";
   
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

     char buffer[MAX_WORD_LENGTH];


      while (fgets(buffer, MAX_WORD_LENGTH, fp)){

            int i = 0;

            while ('a'<=buffer[i] && buffer[i]<='z')
            {
                i++;
                /* code */
            }
            buffer[i] = '\0';
        
        

        insert(t,buffer);


    }

    //  printf("Before displaying, root = %s\n",t->data);

    int ct = count_nodes(t);

    printf("Number of nodes = %d\n",ct);

    display_trie(t,buffer,0);

    t=compress_trie(t);

    ct = count_nodes(t);

    printf("Number of nodes = %d\n",ct);

    // printf("After compress, root = %s\n",t->data);

    printf("\n\n\n");

    // printf("Displaying compress trie\n");

    char store[MAX_WORD_LENGTH];

    display_compress_trie(t,store,0);

    printf("\n\n\n");

    printf("Enter the string for auto completion\n");

    char str[MAX_WORD_LENGTH];

    fgets(str,MAX_WORD_LENGTH,stdin);
    
    auto_complete_compressed_version(t,str); // handle for those str which are not present in trie




}