#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10

typedef struct tree_node{
    int data;
    struct tree_node* left;
    struct tree_node* right;
}tree_node;

void print_inorder(tree_node* t){
    if(t != NULL){
        print_inorder(t->left);
        printf("%d ", t->data);
        print_inorder(t->right);
    }
}

tree_node* create_node(int val){
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    node->data = val;
    node->left = node->right = NULL;

    return node;
}

tree_node* insert_bst(tree_node* t, int val){
    if(t == NULL)
        return create_node(val);
    
    if(val < t->data){
        t->left = insert_bst(t->left, val);
        return t;
    }
    else if(val >= t->data){
        t->right = insert_bst(t->right, val);
        return t;
    }
    return t;
}

int find_bst(tree_node* curr, int val){
    if(curr == NULL)
        return 0;
    else if(val < curr->data)
        return find_bst(curr->left, val);
    else if (val > curr->data)
        return find_bst(curr->right, val);
    else
        return 1;
}

int find(tree_node* curr, int val){
    if(curr == NULL)
        return 0;
    else{
        return curr->data == val || find(curr->left, val)
                                 || find(curr->right, val);
    }
}
int sum(tree_node* curr){
    if(curr != NULL)
        return curr->data + sum(curr->left) + sum(curr->right);
    else 
        return 0;
    
}
int count_leaves(tree_node* curr){
    if(curr == NULL)
        return 0;
    if(curr->left == NULL && curr->right == NULL)
        return 1;
    else{
        return count_leaves(curr->left) + count_leaves(curr->right);
    }
}
void print_even(tree_node* curr){
    if(curr != NULL){
        print_even(curr->left);
        if(curr->data % 2 == 0)
            printf("%d ", curr->data);
        print_even(curr->right);
    }
}
void print_odd(tree_node* curr){
    if(curr != NULL){
        print_odd(curr->left);
        if(curr->data % 2 == 1)
            printf("%d ", curr->data);
        print_odd(curr->right);
    }
}
int tree_height(tree_node* curr){
    if(curr == NULL)
        return 0;
    else{
        int l_height = tree_height(curr->left);
        int r_height = tree_height(curr->right);

        return 1 + ((l_height > r_height) ? l_height : r_height);
    }
}
int num_single_child(tree_node* curr){
    if(curr != NULL){
        if(curr->right != NULL && curr->left != NULL)
            return num_single_child(curr->left) + num_single_child(curr->right);
        if(curr->left == NULL && curr->right != NULL)
            return 1 + num_single_child(curr->right);
        else if(curr->right == NULL && curr->left != NULL)
            return 1 + num_single_child(curr->left);
    }
    return 0;    
}
tree_node* bst_largest(tree_node* curr){
    if(curr == NULL)
        return NULL;
    if(curr->right == NULL)
        return curr;
    return bst_largest(curr->right);
}
int find_below(tree_node* root, int val){
    if(root == NULL)
        return val;
    
    int left = find_below(root->left, val);
    int right = find_below(root->right, val);
    int cmpval = val;
    if(left < val && right < val){
        if(left > right) 
            cmpval = left;
        else 
            cmpval = right;
    }
    else{
        if(left < val)
            cmpval = left;
        else if(right < val)
            cmpval = right;
    }
    if(root->data < val && root->data > cmpval)
        cmpval = root->data;

    return cmpval;
}
int height(tree_node* root){
    if(root==NULL) return 0;
    if(root->left == NULL && root->right == NULL)
        return 1;
}

tree_node* findNode(tree_node* root, int val){
    if(root == NULL) return NULL;

    if(val < root->data)
        return findNode(root->left, val);
    else if(val > root->data)
        return findNode(root->right, val);
    else
        return root;
}
tree_node* parent(tree_node* root, tree_node* node){
    if(root == NULL || node == root)
        return NULL;
    
    if(root->left == node || root->right == node)
        return root;
    if(node->data < root->data)
        return parent(root->left, node);
    else if(node->data > root->data)
        return parent(root->right, node);
    
    return NULL;
}


int main(){
    srand(time(NULL));

    tree_node* root = NULL;
    int size = MAX_SIZE;
    int items[size];
    int s = 0;
    for(int i = 0; i<size; i++){
        items[i] = rand() % (size*10);
        s += items[i];
        root = insert_bst(root, items[i]);
        // printf("%d ", items[i]);
        // root = insert_bst(root, i+1);
    }
    printf("\n");
    print_inorder(root);
    printf("\n");

    return 0;
}