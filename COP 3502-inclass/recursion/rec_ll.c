#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;

node* insert(node* list, int d){
    if(list == NULL){
        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = d;
        newnode->next = NULL;
        return newnode;
    }
    else if(list->next == NULL){
        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = d;
        newnode->next = NULL;
        list->next = newnode;
        return list;
    }
    else{
        list->next = insert(list->next, d);
        return list;
    }
}
node* del(node* list, int d){
    if(list == NULL) return NULL;
    else if(list->data == d){
        node* temp = list;
        list = list->next;
        free(temp);
        return list;
    }
    else{
        list->next = del(list->next, d);
        return list;
    }
}

void print(node* list){
    if(list == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", list->data);
    print(list->next);
}
void freeList(node* list){
    if(list == NULL) return;
    else if(list->next == NULL){
        free(list);
    }
    else{
        freeList(list->next);
        free(list);
    }
}
void copy(node *q, node** s){
    if(q == NULL) return;

    *s = (node*)malloc(sizeof(node));
    (*s)->data = q->data;
    (*s)->next = NULL;
    copy(q->next, &(*s)->next);
}

int main(){
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
            printf("\n");
        }
        else if (choice == 2)
        { // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
            // Look at the list
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

    return 0;
}