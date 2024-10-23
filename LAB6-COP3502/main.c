/* COP 3502C Lab 6
This program is written by: Jason Laureano */

#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

struct node{
    int data;
    struct node* next;
};

// helper function to create a node with a given integer 
struct node* createNode(int d){
    struct node* temp = (struct node*)malloc((sizeof(struct node))); 
    temp->data = d;
    temp->next = NULL;
    return temp;
}

// sorted insert into a linked list by ascending order
struct node* insert(struct node* list, int d){
    if(list == NULL){
        return createNode(d);
    }
    if(list->data > d){
        struct node* in = createNode(d);
        in->next = list;
        return in;
    }
    list->next = insert(list->next, d);
    return list;
}

// Deletes an item with a specified value from the list
struct node* del(struct node* list, int d){
    if(list == NULL){
        printf("Item not found...\n");
        return list;
    }
    if(list->data == d){
        struct node* next = list->next;
        free(list);
        return next;
    }
    list->next = del(list->next, d);
    return list;
}

// Prints the list
void print(struct node* list){
    if(list != NULL){
        printf("->%d", list->data);
        print(list->next);
    }
}

// Frees the memory from the linked list
void freeList(struct node* list){
    if(list == NULL)
        return;
    freeList(list->next);
    free(list);
}

// Copies the values from linked list q into new nodes for the linked list s
void copy(struct node* q, struct node** s){
    if(q == NULL){
        *s = NULL;
    }
    else{
        struct node* temp = createNode(q->data);
        *s = temp;
        copy(q->next, &(*s)->next);
    }
}

int main() {
    atexit(report_mem_leak);
    int number = 0, choice=0;
    struct node *pList=NULL;
    struct node *nList = NULL;
    // Let the user add values until they enter -1.
    while(choice!= 4)
    {
        // Get the operation.
        printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
        scanf("%d", &choice);
        printf("Your choice is %d\n", choice);
        // Execute the operation.
        if (choice == 1)
        {
            // Get the number.
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
            // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            //printf("\n");
        }
        else if (choice == 2)
        {   // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
            // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            //printf("\n");
        }
        else if (choice == 3)
        {
            if (nList)
                freeList(nList);
            copy(pList, &nList); //passing reference of nList as it is not returning anything
            // Look at the list.
            printf("Items in NEW linked list: ");
            print(nList);
            // printf("\n");
        }
        else
        {
            break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("\nBye..\n");
    return 0;
}