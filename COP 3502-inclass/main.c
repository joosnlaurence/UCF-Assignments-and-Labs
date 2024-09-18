#include <stdio.h>
#include <stdlib.h>
#define EMPTY -999

typedef struct node{
    int data;
    struct node* next;
}node;

typedef struct nodeQueue{
    node* front;
    node* back;
}nodeQueue;
typedef struct arrQueue{
    int* nums;
    int noe; // NUmber of elements
    int front, size;
}arrQueue;

// int enQueue(queue* q, int item){

// }
void initArrQueue(arrQueue* q, int size){
    //q = (arrQueue*)malloc(sizeof(arrQueue));
    //q->size = 0;
    q->nums = (int*)malloc(sizeof(int) * size);
    q->size = size;
    q->front = 0;
    q->noe = 0;
}
void enQueueArr(arrQueue* q, int item){
    if(q->noe == q->size){
        // if FULL, realloc arrQueue and copy values in i < q->front to new space
        q->size *= 2;
        q->nums = (int*)realloc(q->nums, sizeof(int) * q->size);
        
        for(int i = 0; i<q->front; i++){
            q->nums[q->noe + i] = q->nums[i];
        }
        // int i = (q->front + q->noe) % q->size;
        // q->noe++;
        // q->nums[i] = item;
    }
    int index = (q->front + q->noe) % q->size; 
    q->noe++;
    q->nums[index] = item;
}
int deQueueArr(arrQueue* q){
    if(empty(q)){
        printf("EMPTY\n");
        return EMPTY;
    }
    q->noe--;
    int val = peek(q);
    q->front = (q->front + 1) % q->size;
    return val;
}

void display(arrQueue* q){
    if(empty(q))
        printf("EMPTY QUEUE");
    int i = 0;
    while(i < q->noe){
        printf("%d ", q->nums[(q->front + i) % q->size]);
        i++;
    }
    printf("\nFront: %d\n", q->front);
    printf("Noe: %d\n", q->noe);
    printf("Size: %d\n\n", q->size);
}

int empty(arrQueue* q){
    return q->noe == 0;
}
int peek(arrQueue* q){
    return q->nums[q->front];
}

int main()
{
    arrQueue* queue = (arrQueue*)malloc(sizeof(arrQueue));
    initArrQueue(queue, 1);

    
    // for(int i = 0; i<3; i++){
    //     printf("%d deleted from the queue\n", deQueueArr(queue));
    // }
    // display(queue);
    while(1){
        int ele, ch;
        printf("1. Enqueue 2. Dequeue 0. Exit: ");
        scanf("%d", &ch);
        switch(ch){
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &ele);
                enQueueArr(queue, ele);
                break;
            case 2:
                printf("Dequeueing %d\n", deQueueArr(queue));
                break;
            case 0:
                return 0;
        }
        display(queue);
    }

    return 0;
}