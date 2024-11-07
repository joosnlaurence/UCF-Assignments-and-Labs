#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct tree_node{
    int data;
    struct tree_node* left;
    struct tree_node* right;
}tree_node;


void print_preorder(tree_node* t){
    if(t != NULL){
        printf("%d ", t->data);
        print_preorder(t ->left);
        print_preorder(t->right);
    }
}
void print_inorder(tree_node* t){
    if(t != NULL){
        print_inorder(t->left);
        printf("%d ", t->data);
        print_inorder(t->right);
    }
}
void print_postorder(tree_node* t){
    if(t != NULL){
        print_postorder(t->left);
        print_postorder(t->right);
        printf("%d ", t->data);
    }
}

tree_node* create_node(int val){
    tree_node* temp = (tree_node*)malloc(sizeof(tree_node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
}


int search_bst(tree_node* t, int val){
    if(t == NULL)
        return 0;
    else if(val < t->data)
        return search_bst(t->left, val);
    else if(val > t->data)
        return search_bst(t->right, val);
    else
        return 1;
}

tree_node* insert_bst(tree_node* t, int val){
    if(t == NULL)
        return create_node(val);
    
    if(val < t->data){
        t->left = insert_bst(t->left, val);
        return t;
    }
    else if(val > t->data){
        t->right = insert_bst(t->right, val);
        return t;
    }
    return t;
}

// tree_node* insert_bst(tree_node* t, int val){
//     if(t == NULL)
//         return create_node(val);
//     else{
//         if(val > t->data){
//             if(t->right != NULL)
//                 t->right = insert_bst(t->right, val);
//             else
//                 t->right = create_node(val);
//         }
//         else if(val < t->data){
//             if(t->left != NULL)
//                 t->left = insert_bst(t->left, val);
//             else
//                 t->left = create_node(val);
//         }
//     }
//     return t;
// }

#define MAX_SIZE 10

int isBSTUtil(tree_node* node, int min, int max){
    if(node == NULL)
        return 1;
    if(node->data < min || node->data > max)
        return 0;
    return isBSTUtil(node->left, min, node->data-1) && 
           isBSTUtil(node->right, node->data+1, max);
}
int isBST(tree_node* root){
    return isBSTUtil(root, 0, MAX_SIZE*10+1);
}

int add(tree_node* curr){
    if(curr != NULL){
        return curr->data + add(curr->left) + add(curr->right);
    }
    else{
        return 0;
    }
}

int main(){
    srand(time(NULL));

    tree_node* root = NULL;
    int size = MAX_SIZE;
    int items[size];
    for(int i = 0; i<size; i++){
        items[i] = rand() % (size*10);
        root = insert_bst(root, items[i]);
        // root = insert_bst(root, i+1);
    }
    print_inorder(root);
    printf("\n");  
    printf("%s\n", (isBST(root)) ? "Valid BST" : "Not a BST");
    printf("%d\n", add(root));


    return 0;
}
