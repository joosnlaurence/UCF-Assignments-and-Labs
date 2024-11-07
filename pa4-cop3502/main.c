#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 25
#define COMMAND_MAX_LEN 14
#define NUM_COMMANDS 6

typedef struct violation_node{
    char name[MAX_NAME_LEN+1];
    int fine_amt; 
    struct violation_node* left;
    struct violation_node* right;
}violation_node;

violation_node* createNode(char name[MAX_NAME_LEN+1], int fine){
    violation_node* node = (violation_node*)malloc(sizeof(violation_node));
    strcpy(node->name, name);
    node->fine_amt = fine;
    node->left = node->right = NULL;

    return node;
}
int findDepth(violation_node* root, violation_node* node){}
violation_node* add(violation_node* root, char name[MAX_NAME_LEN+1], int fine){}

violation_node* search(violation_node* root, char name[MAX_NAME_LEN+1]){}
violation_node* parent(violation_node* root, violation_node* node){}
int maxVal(violation_node* root){}
int isLeaf(violation_node* root){}
int onlyLeftChild(violation_node* node){}
int onlyRightChild(violation_node* node){}
violation_node* deduct(violation_node* root, char name[MAX_NAME_LEN+1], int fine){}

double avgFine(violation_node* root, int sum, int numNodes){}
double avgWrapper(violation_node* root){}

int findHeight(violation_node* root){}
void heightBalance(violation_node* root){}

int calcBelow(violation_node* root, char name[MAX_NAME_LEN+1]){}

void free_mem(violation_node* root){}

int main(){
    int n;
    scanf("%d", &n);

    violation_node* root = NULL;

    char com[COMMAND_MAX_LEN+1];
    char commands[][COMMAND_MAX_LEN+1] = {"add", "deduct", "search", "average",
                                          "height_balance", "calc_below"};
    while(n > 0){
        scanf("%s", com);
        char name[MAX_NAME_LEN+1];
        int fine, depth;
        if(strcmp(com, commands[0]) == 0){
            scanf("%s %d", name, &fine);

            violation_node* temp = add(root, name, fine);
            depth = findDepth(root, temp);

            printf("%s %d %d\n", name, fine, depth);
        }
        else if(strcmp(com, commands[0]) == 0){
            scanf("%s %d", name, &fine);

            violation_node* temp = deduct(root, name, fine);

            if(temp != NULL){
                depth = findDepth(root, temp);
                printf("%s %d %d\n%s removed\n", name, fine, depth, name);
            }
            else
                printf("%s not found\n", name);
        }
        else if(strcmp(com, commands[0]) == 0){
            scanf("%s", name);

            violation_node* temp = search(root, name);
            if(temp != NULL){
                depth = findDepth(root, temp);
                printf("%s %d %d\n", name, temp->fine_amt, depth);
            }
            else
                printf("%s not found\n", name);
        }
        else if(strcmp(com, commands[0]) == 0){
            printf("%ll\n", avgWrapper(root));
        }
        else if(strcmp(com, commands[0]) == 0){
            heightBalance(root);
        }
        else if(strcmp(com, commands[0]) == 0){
            scanf("%s", name);
            printf("%d", calcBelow(root, name));
        }
        else{
            printf(stderr, "Error: Invalid command");
            break;
        }
        n--;
    }

    return 0;
}