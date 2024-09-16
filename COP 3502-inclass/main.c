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
    if(q->noe < q->size){
        // if FULL, realloc arrQueue and copy values in i < q->front to new space
        int i = (q->front + q->noe) % q->size;
        q->noe++;
        q->nums[i] = item;
    }
    else
        printf("\nFULL\n");
}
int deQueueArr(arrQueue* q){
    if(q->noe == 0){
        printf("EMPTY\n");
        return EMPTY;
    }
    q->noe--;
    return q->nums[q->front++];
}

void display(arrQueue* q){
    if(q->noe == 0)
        printf("EMPTY QUEUE");
    int i = 0;
    while(i < q->noe){
        printf("%d ", q->nums[(q->front + i) % q->size]);
        i++;
    }
    puts("");
}

int main()
{
    arrQueue* queue = (arrQueue*)malloc(sizeof(arrQueue));
    initArrQueue(queue, 5);
    for(int i = 0; i<queue->size; i++){
        enQueueArr(queue, i + 1);
    }
    display(queue);
    for(int i = 0; i<3; i++){
        printf("%d deleted from the queue\n", deQueueArr(queue));
    }
    display(queue);

    return 0;
}