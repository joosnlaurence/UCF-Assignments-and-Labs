#include <stdio.h>
#include <stdlib.h>

#define NUM_CHARS 26
#define MAX 1000
#define MAX_STR "1000"


// A trie is a tree in whicn *every node* has 26 children, to store 26 letters in the alphabet
// The string is not stored in the children, rather, the string is stored as a path through the trie
// Count represents the number of that word in the trie.
struct trie_node{
    int count;
    struct trie_node* children[NUM_CHARS];
};

struct trie_node* createNode(){
    struct trie_node* node = (struct trie_node*)malloc(sizeof(struct trie_node));
    node->count = 0;

    for(int i = 0; i<NUM_CHARS; i++){
        node->children[i] = NULL;
    }

    return node;
}
// When you delete a string from a trie, you have to take into account the resulting leaf nodes
// If you see that the count of a leaf node is equal to zero, then you should free that node

void insertStr(struct trie_node* root, char* str){
    char ch = str[0]-(NUM_CHARS == 95 ? ' ' : 'a');
    if(str[0] != '\0'){
        if(root->children[ch] == NULL){
            root->children[ch] = createNode();
        }
        insertStr(root->children[ch], str + 1);
    }
    else
        root->count++;
}

void insertStrIter(struct trie_node* root, char* str){
    int i = 0;
    while(str[i] != '\0'){
        char ch = str[i] - (NUM_CHARS == 95 ? ' ' : 'a');

        if(root->children[ch] == NULL)
            root->children[ch] = createNode();
        root = root->children[ch];
        i++;
    }
    root->count++;
}

int searchTrie(struct trie_node* root, char* str, int i){
    
    if(str[i] == '\0'){
        return root->count;
    }
    char ch = str[i] - (NUM_CHARS == 95 ? ' ' : 'a');
    if(root->children[ch] == NULL)
        return 0;
    
    return searchTrie(root->children[ch], str, i+1); 
}

int isEmpty(struct trie_node* node){
    if(node == NULL) return 0;

    for(int i = 0; i<NUM_CHARS; i++){
        if(node->children[i] != NULL)
            return 0;
    }
    return 1;
}

int deleteString(struct trie_node* root, char* str, int i){
    if(root == NULL) return 0;
    
    if(str[i] == '\0'){
        root->count--;
        return 1;
    }

    char ch = str[i]-(NUM_CHARS == 95 ? ' ' : 'a');
    int found = deleteString(root->children[ch], str, i+1);

    if(found && isEmpty(root->children[ch]) && root->children[ch]->count == 0){
        struct trie_node* temp = root->children[ch];
        root->children[ch] = NULL;
        free(temp);
    }
    return found;
}

void printAllHelper(struct trie_node* root, char* word, int len){
    if(root == NULL) return;
    if(root->count > 0)
        printf("%s\n", word);

    for(int i = 0; i<26; i++){
        word[len] = (char)(i + 'a');
        word[len+1] = '\0';
        printAllHelper(root->children[i], word, len+1);
    }
}

void printAll(struct trie_node* root){
    char word[MAX+1];
    word[0] = '\0';
    printAllHelper(root, word, 0);
}



int main(){
    struct trie_node* root = createNode();

    while(1){
        int ch;
        printf("(1) Insert | (2) Search | (3) Delete\n====================================\n");
        scanf("%d", &ch);
        
        char str[MAX+1];
        switch(ch){
            case 1:
                printf("\nEnter a string to insert: ");
                scanf(" %" MAX_STR "[^\n]", str);
                insertStr(root, str);
                break;
            case 2:
                printf("\nEnter a string to search for: ");
                scanf(" %" MAX_STR "[^\n]", str);
                printf("%s found %d times\n", str, searchTrie(root, str, 0));
                break;
            case 3:
                printf("Enter a string to delete from the trie: ");
                scanf(" %" MAX_STR "[^\n]", str);
                if(deleteString(root, str, 0) == 1){
                    printf("%s was deleted\n\n", str);
                }
                else {
                    printf("%s was not found\n\n", str);
                }
                break;
            case 4:
                printf("Goodbye\n");
                free(root);
                return 0;
            default:
                printf("Invalid Command\n");
                break;
        }
        printf("\n%s\n", "Printing all of the strings...");
        printAll(root);
        puts("");
    }
}
