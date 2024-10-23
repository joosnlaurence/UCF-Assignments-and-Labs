#include <stdio.h>
#include <stdlib.h>
#define EMPTY -9999

typedef struct node{
    int data;
    struct node* next;
}node;
typedef struct queue{
    node* front;
    node* back;
}queue;

node* create_node(int n){
    node* t = (node*)malloc(sizeof(node));
    t->data = n;
    t->next = NULL;
    return t;
}

void initQueue(queue* q){
    q->front = q->back = NULL;
}

void enqueue(queue* q, int n){
    node* t = create_node(n);
    if(q->front == NULL){
        q->front = q->back = t;
    }
    else{
        q->back->next = t;
        q->back = t;
    }
}
int dequeue(queue* q){
    if(q->front == NULL){
        return EMPTY;
    }
    node* temp = q->front;
    q->front = q->front->next;
    int n = temp->data;
    free(temp);

    if(q->front == NULL)
        q->back = NULL;
    return n;
}
void display(queue* q){
    node* temp = q->front;
    printf("Printing queue: \n");
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    queue* q;
    initQueue(q);
    while(1){
        int ch, n;
        printf("0-exit. 1-enqueue. 2-dequeue. 3-display : ");
        scanf("%d", &ch);
        switch(ch){
            case 0:
                return 0;
            case 1:
                printf("Choose an integer to enqueue: ");
                scanf("%d", &n);
                enqueue(q, n);
                display(q);
                break;
            case 2:
                int dq = dequeue(q);
                if(dq == EMPTY)
                    printf("Queue is empty...\n");
                else
                    printf("Dequeuing %d...", dq);
                display(q);
                break;
            case 3:
                display(q);
                break;
            default:
                printf("Invalid option\n\n");
                break;
        }
    }
}