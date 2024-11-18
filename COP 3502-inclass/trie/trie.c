#include <stdio.h>
#include <stdlib.h>

#define NUM_CHARS 95

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

void insertStr(struct trie_node* root, char* str, int i){
    char ch = str[i]-(NUM_CHARS == 95 ? ' ' : 'a');
    if(str[i] == '\0'){
        root->count++;
        return;
    }
    else if(root->children[ch] == NULL){
        root->children[ch] = createNode();
    }
    insertStr(root->children[ch], str, i+1);
}

int searchTrie(struct trie_node* root, char* str, int i){
    if(root == NULL)
        return 0;
    else if(str[i] == '\0'){
        return root->count;
    }
    char ch = str[i] - (NUM_CHARS == 95 ? ' ' : 'a');
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

    if(isEmpty(root->children[ch]) && root->children[ch]->count == 0){
        struct trie_node* temp = root->children[ch];
        root->children[ch] = NULL;
        free(temp);
    }
    return found;
}

#define MAX 1000
#define MAX_STR "1000"

int main(){
    struct trie_node* root = createNode();

    while(1){
        int ch;
        printf("(1) Insert | (2) Search | (3) Delete\n====================================\n");
        scanf("%d", &ch);
        
        char str[MAX+1];
        switch(ch){
            case 1:
                printf("Enter a string to insert: ");
                scanf(" %" MAX_STR "[^\n]", str);
                insertStr(root, str, 0);
                break;
            case 2:
                printf("Enter a string to search for: ");
                scanf(" %" MAX_STR "[^\n]", str);
                printf("%s found %d times\n\n", str, searchTrie(root, str, 0));
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
                return 0;
            default:
                printf("Invalid Command\n");
                break;
        }
    }
}
