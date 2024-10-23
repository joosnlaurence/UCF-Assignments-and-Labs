#include <stdio.h>
#define EMPTY -999
#define MAX_SIZE 5

typedef struct queue{
    int data[MAX_SIZE];
    int front, back;
    int noe, capacity;
}queue;

void initQueue(queue* q){
    q->front = 0;
    q->noe = 0;
    q->capacity = MAX_SIZE;
}

void enqueue(queue* q, int n){
    if(q->noe == q->capacity){
        printf("Queue is full.\n");
        return;
    }
    int back = (q->front + q->noe) % q->capacity;
    q->noe++;
    q->data[back] = n;
}
int dequeue(queue* q){
    if(q->noe == 0){
        return EMPTY;
    }
    q->noe--;
    int data = q->data[q->front];
    q->front = (q->front+1) % q->capacity;
    return data;
}
void display(queue* q){
    if(q->noe == 0)
        printf("Queue is empty...\n\n");
    else{
        printf("Printing queue: ");
        for(int i = 0; i<q->noe; i++){
            int curr = (q->front + i) % q->capacity;
            printf("%d ", q->data[curr]);
        }
        printf("\n\n");
    }
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
                    printf("Dequeuing %d...\n", dq);
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
