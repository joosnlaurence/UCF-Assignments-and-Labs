/* COP3502C: Assignment 5
    This program was created by Jason Laureano
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LEN 25
#define COMMAND_MAX_LEN 14
#define NUM_COMMANDS 6

typedef struct violation_node{
    char name[MAX_NAME_LEN+1];
    int fine_amt;
    int depth; // Keep track of the depth in the tree for every node
    struct violation_node* left;
    struct violation_node* right;
}violation_node;

violation_node* createNode(char name[MAX_NAME_LEN+1], int fine){
    violation_node* node = (violation_node*)malloc(sizeof(violation_node));
    strcpy(node->name, name);
    node->fine_amt = fine;
    node->left = node->right = NULL;
    node->depth = 0;

    return node;
}
violation_node* add(violation_node* root, char name[MAX_NAME_LEN+1], int fine, int depth){
    if(root == NULL){
        violation_node* temp = createNode(name, fine);
        temp->depth = depth;
        printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
        return temp;
    } 

    int cmp = strcmp(name, root->name);
    if(cmp < 0)
        root->left = add(root->left, name, fine, depth+1);
    else if(cmp > 0)
        root->right = add(root->right, name, fine, depth+1);
    else{
        // Add to the fine if the person already has a fine
        root->fine_amt += fine;
        root->depth = depth;
        printf("%s %d %d\n", name, root->fine_amt, depth);
    }

    return root;
}

violation_node* search(violation_node* root, char name[MAX_NAME_LEN+1], int depth){
    if(root == NULL) return NULL;
    
    int cmp = strcmp(name, root->name);
    // Update depths upon every search to account for depth changes due to deletion 
    if(cmp < 0){
        root->depth = depth;
        return search(root->left, name, depth+1);
    }
    else if(cmp > 0){
        root->depth = depth;
        return search(root->right, name, depth+1);
    }
    else{
        root->depth = depth;
        return root;
    }
}
violation_node* parent(violation_node* root, violation_node* node){
    if(root == NULL || node == root)
        return NULL;
    
    if(root->left == node || root->right == node)
        return root;
    int cmp = strcmp(node->name, root->name);
    if(cmp < 0)
        return parent(root->left, node);
    else if(cmp > 0)
        return parent(root->right, node);
    else
        return NULL;
}
violation_node* maxVal(violation_node* root){
    if(root == NULL) return 0;

    if(root->right != NULL)
        return maxVal(root->right);
    return root;
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
violation_node* delete(violation_node* root, violation_node* delnode){
    if(!root || !delnode) return root;
    
    violation_node *new_delnode, *save_node;
    violation_node* p; // Parent of delnode
    char save_name[MAX_NAME_LEN+1];

    p = parent(root, delnode);
    int cmp;
    if(p != NULL)
        cmp = strcmp(delnode->name, p->name);

    if(isLeaf(delnode)){
        if(p == NULL){
            free(delnode);
            return NULL;
        }
        else if(cmp < 0)
            p->left = NULL;
        else
            p->right = NULL;
        free(delnode);

        return root;
    }
    else if(onlyLeftChild(delnode)){
        if(p == NULL){
            save_node = delnode->left;
            free(delnode);
            save_node->depth--;
            return save_node;
        }
        else if(cmp < 0){
            p->left = p->left->left;
        }
        else{
            p->right = p->right->left;
        }
        free(delnode);
        return root;
    }
    else if(onlyRightChild(delnode)){
        if(p == NULL){
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }
        else if(cmp < 0){
            p->left = p->left->right;
        }
        else{
            p->right = p->right->right;
        }
        free(delnode);
        return root;
    }

    new_delnode = maxVal(delnode->left);
    // Update the values of the node that will replace the deleted node
    strcpy(save_name, new_delnode->name);
    delnode->fine_amt = new_delnode->fine_amt;

    delete(root, new_delnode);

    strcpy(delnode->name, save_name);

    return root;
}
// Wrapper for delete that includes printf outputs and changes total final amount accordingly
violation_node* deduct(violation_node* root, char name[MAX_NAME_LEN+1], int fineDeduct){
    violation_node* temp = search(root, name, 0);
    if(temp == NULL){
        printf("%s not found\n", name);
        return root;
    }

    // Delete node if deduction will result in 0 or negative fine
    if(temp->fine_amt <= fineDeduct){
        root = delete(root, temp);
        printf("%s removed\n", name);
        return root;
    }
    else{
        temp->fine_amt -= fineDeduct;
        printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
        return root;
    }        
}

// Update sum and numNodes simultaneously while traveling through the tree
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

    // Avoid divide by zero
    return (numNodes == 0) ? 0 : (double)sum / numNodes;
}

int findHeight(violation_node* root){
    if(root == NULL) return -1;
    
    // Iterate through each node in left and right subtrees
    int lh = 1 + findHeight(root->left);
    int rh = 1 + findHeight(root->right);

    return (lh > rh) ? lh : rh;
}
void heightBalance(violation_node* root){
    if(root == NULL) return;
    
    // Find the heights of the left and right subtree
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
    // Find first instance of node name being lexicographically smaller
    // than given name 
    if(cmp < 0){
        return calcBelow(root->left, name);
    }
    // Node names less than current node will all be less than name, so sum them
    // Find the next instance of node name being smaller than given name 
    //  and repeat 
    return root->fine_amt + sum(root->left) + calcBelow(root->right, name);
}

void free_mem(violation_node* root){
    if(root != NULL){
        free_mem(root->left);
        free_mem(root->right);
        free(root);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    violation_node* root = NULL;

    char com[COMMAND_MAX_LEN+1];
    while(n > 0){
        scanf("%s", com);
        char name[MAX_NAME_LEN+1];
        int fine;
        if(strcmp(com, "add") == 0){
            scanf("%s %d", name, &fine);

            root = add(root, name, fine, 0);
        }
        else if(strcmp(com, "deduct") == 0){
            scanf("%s %d", name, &fine);

            root = deduct(root, name, fine); 
        }
        else if(strcmp(com, "search") == 0){
            scanf("%s", name);

            violation_node* temp = search(root, name, 0);
            if(temp != NULL){
                printf("%s %d %d\n", name, temp->fine_amt, temp->depth);
            }
            else
                printf("%s not found\n", name);
        }
        else if(strcmp(com, "average") == 0){
            printf("%.2lf\n", average(root));
        }
        else if(strcmp(com, "height_balance") == 0){
            heightBalance(root);
        }
        else if(strcmp(com, "calc_below") == 0){
            scanf("%s", name);
            printf("%d\n", calcBelow(root, name));
        }
        n--;
    }
    free_mem(root);

    return 0;
}
