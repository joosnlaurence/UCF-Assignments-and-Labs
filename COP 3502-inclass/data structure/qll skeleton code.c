// Example of how to implement a queue with a linked list. 
#include <stdio.h>
#include<stdlib.h>

#define EMPTY -1

// Stores one node of the linked list.
struct node {
    int data;
    struct node* next;
};

// Stores our queue.
struct queue {
    struct node* front;
    struct node* back;
};

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);
void displayQueue(struct queue* MyQueuePtr);

int main() {
    
    // Allocate space for our queue and initialize it.
    struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
    init(MyQueuePtr);

    int choice;
    int data;

    int i;
    
   while (1)
    {
        printf("\n1.Insert element to queue \n");
        printf("2.Delete element from queue \n");
        printf("3. Display all elements of queue \n");
        printf("4.Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("\nWhat data you want to put in the queue?: ");
                scanf("%d", &data);
                enqueue(MyQueuePtr, data);
                displayQueue(MyQueuePtr);
                break;
            case 2:
                data = dequeue(MyQueuePtr);
                if(data!=EMPTY)
                {
                    printf("\n%d deleted from queue\n", data);
                    displayQueue(MyQueuePtr);
                }
                else
                  printf("Empty queue\n");
                break;
            case 3:
                displayQueue(MyQueuePtr);
                break;
            case 4:
                exit(1);
            default:
                printf("Wrong choice \n");
        } /*End of switch*/
    } /*End of while*/
    return 0;
} /*End of main()*/

void displayQueue(struct queue* MyQueuePtr)
{
  struct node *t =  MyQueuePtr->front;
  while(t)
  {
    printf("%d ", t->data);
    t = t->next;
  }
}
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
//                 empty queue.
void init(struct queue* qPtr) {
	//initialize front and back to NULL
     qPtr->front = qPtr->back = NULL;   
}

// Pre-condition: qPtr points to a valid struct queue and val is the value to
//                enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
//                 no change will be made to the queue and 0 will be returned.
int enqueue(struct queue* qPtr, int val) {
	//create a new node, put val inside this and next to NULL
	//Now we need to append this new node after the current back and then move the back to the new node
	//However, in a special case, we need to update front and back to the new node if the queue is empty.

    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    if(!newnode) return 0;
    newnode->data = val;
    newnode->next = NULL;
    if(empty(qPtr)){
        qPtr->front = newnode;
    }
    else{
        qPtr->back->next = newnode;
    }
    qPtr->back = newnode;
    // No change to the queue was made because we couldn't find space for our
    // new enqueue.
       
    return 1;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
//                 at the front of the queue is deleted from the queue and 
//                 returned. Otherwise, -1 is returned to signify that the queue
//                 was already empty when the dequeue was attempted.
int dequeue(struct queue* qPtr) {
	//we need to return the front item from the queue
	//so, save the front data, move front forward to the next node, and return the saved data. Make sure to free the old front using a temp pointer
	//There are two special case to handle:
	//1. If the front was NULL, then nothing to be removed. Return EMPTY constant
	//2. If front is not NULL, but after moving front forward, it becomes NULL(We had only one item in the list), then we need to make sure to update front and back to NULL as there is nothing left in the queue 
    if(empty(qPtr)) return -1;
    int data = qPtr->front->data;
    struct node* temp = qPtr->front;
    qPtr->front = qPtr->front->next;
    free(temp);

    return data;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int empty(struct queue* qPtr) {
   return qPtr->front == NULL;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value 
//                 stored at the front of the queue is returned. Otherwise,
//                 -1 is returned to signify that this queue is empty.
int peek(struct queue* qPtr) {
    return qPtr->front->data;
}
