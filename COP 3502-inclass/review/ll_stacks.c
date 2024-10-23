#include <stdio.h>
#include <stdlib.h>
#define EMPTY -9999

typedef struct node{
    int data;
    struct node* next;
}node;
// typedef struct stack{
//     node* top;
// }stack;

node* createNode(int n){
    node* temp = (node*)malloc(sizeof(node));
    temp->data = n;
    temp->next = NULL;
    return temp;
}

void push(node** st, int n){
    node* temp = createNode(n);
    if(st != NULL){
        temp->next = *st;
    }
    *st = temp;
}
int pop(node** st){
    if(*st == NULL)
        return EMPTY;

    node* temp = *st;
    *st = (*st)->next;
    int n = temp->data;
    free(temp);
    return n;
}
void display(node** st){
    if(*st == NULL){
        printf("Stack is empty...\n\n");
        return;
    }
    node* temp = *st;
    printf("Printing Stack: ");
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n\n");
}

int main(){
}