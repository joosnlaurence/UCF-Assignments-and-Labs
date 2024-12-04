#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

node* createNode(int val){
    node* n = (node*)malloc(sizeof(node));
    n->data = val;
    n->left = n->right = NULL;

    return n;
}

void printInorder(node* root){
    if(root != NULL){
        printInorder(root->left);
        printf("%d ", root->data);
        printInorder(root->right);
    }
}
void printPreorder(node* root){
    if(root != NULL){
        printf("%d ", root->data);
        printInorder(root->left);
        printInorder(root->right);
    }
}

node* insert(node* root, int val){
    if(root == NULL) return createNode(val);

    if(val < root->data){
        root->left = insert(root->left, val);
    }
    else if(val >= root->data){
        root->right = insert(root->right, val);
    }

    return root;
} 

int hasOnlyLeftChild(node* n){
    return n->left && !(n->right);
}
int hasOnlyRightChild(node* n){
    return !(n->left) && n->right;
}
int isLeafNode(node* n){
    return !(n->left) && !(n->right);
}
node* findNode(node* root, int val){
    if(root == NULL) return NULL;
    
    if(val < root->data)
        return findNode(root->left, val);
    else if(val > root->data)
        return findNode(root->right, val);
    else
        return root;
}
node* findParent(node* root, node* n){
    if(root == NULL || root == n) 
        return NULL;
    if(root->left == n || root->right == n)
        return root;
    else if(n->data < root->data)
        return findParent(root->left, n);
    else if(n->data > root->data)
        return findParent(root->right, n);

    return NULL;
}
node* findMax(node* root){
    if(root == NULL) return NULL;
    if(root->right != NULL){
        return findMax(root->right);
    }
    return root;
}


node* delete(node* root, int val){
    node *delnode, *savenode, *new_delnode;
    int save_val; 

    delnode = findNode(root, val);
    node* parent = findParent(root, delnode);

    if(root == NULL) return NULL;

    if(isLeafNode(delnode)){
        if(parent == NULL){
            free(delnode);
            return NULL;
        }
        else if(delnode->data < parent->data){
            free(parent->left);
            parent->left = NULL;
        }
        else{
            free(parent->right);
            parent->right = NULL;
        }
        return root;
    }
    else if(hasOnlyLeftChild(delnode)){
        if(parent == NULL){
            savenode = delnode->left;
            free(delnode);
            return savenode;
        }
        if(val < parent->data){
            savenode = parent->left;
            parent->left = parent->left->left;
            free(savenode);   
        }
        else{
            savenode = parent->right;
            parent->right = parent->right->left;
            free(savenode);
        }
        return root;
    }
    else if(hasOnlyRightChild(delnode)){
        if(parent == NULL){
            savenode = delnode->right;
            free(delnode);
            return savenode;
        }
        if(val < parent->data){
            savenode = parent->left;
            parent->left = parent->left->right;
            free(savenode);   
        }
        else{
            savenode = parent->right;
            parent->right = parent->right->right;
            free(savenode);
        }
        return root;
    }


    new_delnode = findMax(delnode->left);
    save_val = new_delnode->data;

    delete(root, save_val);

    delnode->data = save_val;

    return root;
}

int main(){
    int n = 10;
    int arr[n];
    node* root = NULL;

    for(int i = 0; i<n; i++){
        arr[i] = rand() % (n*100); 
        root = insert(root, arr[i]);
    }
    
    printInorder(root);
    puts("\n");    
    printPreorder(root);
    puts("\n"); 

    delete(root, 386);

    printInorder(root);
    puts("\n");    
    printPreorder(root);

    return 0;
}