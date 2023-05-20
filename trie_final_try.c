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

// not the compressed version!

void print_trie_helper(TrieNode* root, char* store, int ind) {

    printf("root = %s\n",root->data);

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

TrieNode* compress_trie(TrieNode *root){



    if (!root) return root;
    
    TrieNode*child = NULL;

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            child = root->children[i];

            
        //    printf("Before function call, root = %s\n",root->data);

        //    printf("Before function call, child = %s\n",child->data);

            // printf("********************************************\n");

            child =  compress_trie(child);

            // printf("After function call, root = %s\n",root->data);


            // printf("After function call, child = %s\n",child->data);

            // printf("********************************************\n");

            root->children[i] = child;


            // ye neeche wala condition modify karna padega

            // if (root && root->data[0] == '\0'){

            //     printf("I am here\n");

            //     return root;
            // }
        }
         

    
    }

      
        /* code */  


    int childCount = 0;
    // TrieNode*child = NULL;

    for (int i = 0; i < size; i++)
    {
        if (root->children[i]){

            childCount++;

            child = root->children[i];

            if (childCount>1) return root;
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

    return root ;

    
    
    
}

void display_compress_trie(TrieNode *t,char *buffer, int depth){

    // atleast all roots are getting printed

    if (!t){

        // printf("About to return\n");

        return;
    }

   // printf("root = %s ",t->data);

    //printf("buffer before insertion = ");

    //print_buffer(buffer,depth);

    //("\n");

    // printf("Inside, display compress trie, root = %s\n",t->data);

    TrieNode *child;


    for (int i = 0; i < size; i++)
    {

        // printf("i = %d\n",i);

        
        if (t->children[i]){
            
            // printf("Here?\n");

            child = t->children[i];

            // printf("Inside Non Null child\n");

            // printf("root = %s\n",t->data);

            // printf("child = %s\n",child->data);

            int j = 0;

            while (j<child->index)
            {

                // printf("root = %s\n",t->data);

                // printf("Printing buffer before incrementing depth\n");

                // print_buffer(buffer,depth);

                //printf("child = %s\n",child->data);

                buffer[depth++] = child->data[j];

                // printf("buffer after insertion = ");

                // print_buffer(buffer,depth);

                //  printf("\n");

                //printf("buffer after incrementing depth and inserting jth char of child = ");

               // print_buffer(buffer,depth);

                //printf("\n");

                j++;
                
                /* code */
            }


            if(child->isTerminal){

                // printf("I am here\n");pri

                buffer[depth] = '\0';

                printf("buffer inside the base case = ");

                printf("%s\n",buffer);

               

                //printf("After resetting, buffer = ");

                //print_buffer(buffer,depth);

                //printf("\n");
                
            }

            //printf("Just before function call, buffer = ");

            //print_buffer(buffer,depth);

            //printf("\n");

            display_compress_trie(child,buffer,depth);

             for (int i = 0; i < child->index; i++)
                {
                    depth--;
                    /* code */
                }

           // printf("root = %s\n",t->data);

            //printf("Just after function call, buffer = ");

            //print_buffer(buffer,depth);

            //printf("\n");

            //printf("*******************************************\n");
            
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


                // printf("Before leaving, depth = %d\n",(*depth));

                auto_complete_recursion_2nd_step(child,key,buffer,depth);

                //(*depth)--; // this was the error   *(depth)-- lol

                //print_buffer(buffer,*depth);

                
                
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

    // printf("root = %s\n",root->data);

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

    // problem is that I need to create root with null char as data and then 
    // isnert all the nodes as it children


    TrieNode*t = init();
    // insert(t,"adgqs");
    // insert(t,"adgqr");
    // insert(t,"aez");
    // insert(t,"aeo");
    // insert(t,"afm");
    // insert(t,"bn");
    // insert(t,"cp");
    // insert(t,"abandon");
    // insert(t,"are");
    // insert(t,"assessment");
    // insert(t,"assess");
    // insert(t,"assistance");
    // insert(t,"boo");
    // insert(t,"boorish");
    // insert(t,"brave");
    // insert(t,"sahil");
    insert(t,"bear");
    insert(t,"bell");
    insert(t,"bid");
    insert(t,"bull");
    insert(t,"buy");
    insert(t,"sell");
    insert(t,"stock");
    insert(t,"stop");
    insert(t,"assessment");
    insert(t,"assistance");
    // insert(t,"assess");

    int ct = count_nodes(t);

    printf("count1 = %d\n",ct);
  
    // printf("After insertion, root = %s\n",t->data);
    
   char buffer[MAX_WORD_LENGTH];
    // display_trie(t, buffer, 0);
    // compress_trie(t);

    display_trie(t,buffer,0); // working

    printf("\n\n\n");

    // auto_complete(t,"a"); 
    // auto_complete(t,"b"); 
    auto_complete(t,"b");

    printf("\n\n\n");

    t = compress_trie(t);

    //  auto_complete(t,"b");

    //      printf("\n\n\n");

    ct = count_nodes(t);

    printf("count2 = %d\n",ct);

    // printf("After compression, root = %s\n",t->data);

    char buff[MAX_WORD_LENGTH];


    display_compress_trie(t,buff,0);




   


    
    // printf("display compress function over\n");
  

    


    




















    return 0;
}