#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 25
#define COMMAND_MAX_LEN 14
#define NUM_COMMANDS 6

typedef struct violation_node{
    char name[MAX_NAME_LEN+1];
    int fine_amt;
    int depth; 
    struct violation_node* left;
    struct violation_node* right;
}violation_node;
void print_inorder(violation_node* root){
    if(root != NULL){
        print_inorder(root->left);
        printf("(%s %d %d) ", root->name, root->fine_amt, root->depth);
        print_inorder(root->right);
    }
}

violation_node* createNode(char name[MAX_NAME_LEN+1], int fine){
    violation_node* node = (violation_node*)malloc(sizeof(violation_node));
    strcpy(node->name, name);
    node->fine_amt = fine;
    node->left = node->right = NULL;
    node->depth = 0;

    return node;
}
int findDepth(violation_node* root, char name[MAX_NAME_LEN+1]){
    if(root == NULL) return -1;
    
    int cmp = strcmp(name, root->name);
    int depth;

    if(cmp < 0)
        depth = findDepth(root->left, name);
    else if(cmp > 0)
        depth = findDepth(root->right, name);
    else
        depth = 0;
    
    return (depth == -1) ? -1 : depth + 1;
}
violation_node* addHelper(violation_node* root, char name[MAX_NAME_LEN+1], int fine, int depth){
    if(root == NULL){
        violation_node* temp = createNode(name, fine);
        temp->depth = depth;
        return temp;
    } 

    int cmp = strcmp(name, root->name);
    if(cmp < 0)
        root->left = addHelper(root->left, name, fine, depth+1);
    else if(cmp > 0)
        root->right = addHelper(root->right, name, fine, depth+1);
    else{
        root->fine_amt += fine;
    }

    return root;
}
violation_node* add(violation_node* root, char name[MAX_NAME_LEN+1], int fine){
    return addHelper(root, name, fine, 0);
}

violation_node* search(violation_node* root, char name[MAX_NAME_LEN+1]){
    if(root == NULL) return NULL;
    
    int cmp = strcmp(name, root->name);
    if(cmp < 0)
        return search(root->left, name);
    else if(cmp > 0)
        return search(root->right, name);
    else
        return root;
}
violation_node* parent(violation_node* root, violation_node* node){}
violation_node* maxVal(violation_node* root){
    if(root == NULL) return 0;

    if(root->right != NULL)
        return maxVal(root->right);
    return root->fine_amt;
}
int isLeaf(violation_node* node){
    return node->left == NULL && node->right == NULL;
}
int onlyLeftChild(violation_node* node){
    return node->left != NULL && node->right == NULL;
}
int onlyRightChild(violation_node* node){
    return node->right != NULL && node->left == NULL;
}
violation_node* remove(violation_node* root, violation_node* node){

}
violation_node* deduct(violation_node* root, char name[MAX_NAME_LEN+1], int fineDeduct){
    violation_node* temp = search(root, name);
    if(temp == NULL) return NULL;

    if(temp->fine_amt < fineDeduct)
        temp->fine_amt = 0;
    else
        temp->fine_amt -= fineDeduct;

    return temp;
}

void avgHelper(violation_node* root, int* sum, int* numNodes){
    if(root == NULL) return;

    *sum += root->fine_amt;
    (*numNodes)++;

    avgHelper(root->left, sum, numNodes);
    avgHelper(root->right, sum, numNodes);
}
double average(violation_node* root){
    int sum = 0, numNodes = 0;
    avgHelper(root, &sum, &numNodes);
    return (double)sum / numNodes;
}

int findHeight(violation_node* root){
    if(root == NULL) return -1;
    
    int lh = 1 + findHeight(root->left);
    int rh = 1 + findHeight(root->right);

    return (lh > rh) ? lh : rh;
}
void heightBalance(violation_node* root){
    if(root == NULL) return;
    
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    int isBalanced = leftHeight == rightHeight;
    printf("left height = %d right height = %d %s\n", leftHeight, rightHeight,
                                                    (isBalanced) ? "balanced":"not balanced");
}

int sum(violation_node* root){
    if(root != NULL){
        return root->fine_amt + sum(root->left) + sum(root->right);
    }
    return 0;
}
int calcBelow(violation_node* root, char name[MAX_NAME_LEN+1]){
    if(root == NULL) return 0;

    int cmp = strcmp(name, root->name);
    if(cmp <= 0){
        return calcBelow(root->left, name);
    }
    return root->fine_amt + sum(root->left) + calcBelow(root->right, name);
}

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

            root = add(root, name, fine);
            violation_node* temp = search(root, name);

            printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
        }
        else if(strcmp(com, commands[1]) == 0){
            scanf("%s %d", name, &fine);

            violation_node* temp = deduct(root, name, fine);
            if(temp != NULL){
                printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
                if(temp->fine_amt == 0){
                    root = remove(root, temp);
                    printf("%s removed\n", name);
                }
            }
            else
                printf("%s not found\n", name);
        }
        else if(strcmp(com, commands[2]) == 0){
            scanf("%s", name);

            violation_node* temp = search(root, name);
            if(temp != NULL){
                printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
            }
            else
                printf("%s not found\n", name);
        }
        else if(strcmp(com, commands[3]) == 0){
            printf("%.2lf\n", average(root));
        }
        else if(strcmp(com, commands[4]) == 0){
            heightBalance(root);
        }
        else if(strcmp(com, commands[5]) == 0){
            scanf("%s", name);
            printf("name %d\n", calcBelow(root, name));
        }
        else{
            fprintf(stderr, "Error: Invalid command");
            break;
        }
        // print_inorder(root);
        // puts("");
        n--;
    }

    return 0;
}