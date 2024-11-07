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
tree_node* minVal(tree_node* root){
    if(root == NULL) return NULL;

    if(root->left != NULL)
        return minVal(root->left);
    else 
        return root;
}
tree_node* maxVal(tree_node* root){
    if(root == NULL) return NULL;

    if(root->right != NULL)
        return maxVal(root->right);
    else
        return root;
}
int isLeaf(tree_node* node){
    return node->left == NULL && node->right == NULL;
}
int hasOnlyLeftChild(tree_node* node){
    return node->left != NULL && node->right == NULL;
}
int hasOnlyRightChild(tree_node* node){
    return node->right != NULL && node->left == NULL;
}
tree_node* delete(tree_node* root, int val){
    tree_node *delnode, *new_delnode, *save_node;
    tree_node* p; // Parent of delnode
    int save_val;

    delnode = findNode(root, val);
    if(delnode == NULL) return NULL;
    p = parent(root, delnode);

    if(isLeaf(delnode)){
        if(p == NULL){
            free(delnode);
            return NULL;
        }
        else if(val < p->data)
            p->left = NULL;
        else
            p->right = NULL;
        free(delnode);

        return root;
    }
    else if(hasOnlyLeftChild(delnode)){
        if(p == NULL){
            save_node = delnode->left;
            free(delnode);
            return save_node;
        }
        else if(val < p->data){
            p->left = p->left->left;
        }
        else{
            p->right = p->right->left;
        }
        free(delnode);
        return root;
    }
    else if(hasOnlyRightChild(delnode)){
        if(p == NULL){
            save_node = delnode->right;
            free(delnode);
            return save_node;
        }
        else if(val < p->data){
            p->left = p->left->right;
        }
        else{
            p->right = p->right->right;
        }
        free(delnode);
        return root;
    }

    new_delnode = minVal(delnode->right);
    save_val = new_delnode->data;

    delete(root, save_val);

    delnode->data = save_val;

    return root;
}

int main(){
    // srand(time(NULL));

    tree_node* root = NULL;
    int size = MAX_SIZE;
    int items[size];
    int s = 0;
    for(int i = 0; i<size; i++){ 
        items[i] = rand() % (size*100);
        s += items[i];
        root = insert_bst(root, items[i]);
        // printf("%d ", items[i]);
        // root = insert_bst(root, i+1);
    }
    printf("\n");
    print_inorder(root);
    printf("\n");

    for(int i = 0; i<size; i++){
        root = delete(root, items[i]);
        printf("\n");
        print_inorder(root);
        printf("\n");
    }
    printf("\n");
    print_inorder(root);
    printf("\n");

    return 0;
}