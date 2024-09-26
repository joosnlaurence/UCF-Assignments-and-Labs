/* COP 3502C Assignment 2
This program is written by: Jason Laureano */
#include <stdio.h>
#include <stdlib.h>
#define MAX_GARAGES 10

typedef struct Student{
    int sequenceNumber;
    struct Student* next;
}Student;
typedef struct GarageQueue{
    Student *front, *back;
    int nodeCount; // number of students
    int k; // number of students skipped before elimination
    int th; // threshold for students
    int gNum; // garage number
}GarageQueue;

Student* createStudent(int sequence);
void createReverseCircle(GarageQueue* gq);

// return the front student in the queue
Student* peek(const GarageQueue* gq){
    if(gq != NULL)
        return gq->front;
    return NULL;
}
// check if the queue is empty
int isempty(const GarageQueue* gq){
    if(gq == NULL)
        return -1;
    return gq->nodeCount == 0;
}

// add a student with a given sequence number to the back of the queue
void enqueue(GarageQueue* gq, int sequence){
    Student* st = createStudent(sequence);

    if(isempty(gq)){
        gq->front = st; 
        st->next = st;
    } 
    else{
         gq->back->next = st; 
         st->next = gq->front;
    }
    gq->back = st;
    gq->nodeCount++;
}
// removes and returns the student from the front of the queue
Student* dequeue(GarageQueue* gq){
    if(!isempty(gq)){
        gq->nodeCount--;
        Student* dequeued = gq->front;
        gq->front = dequeued->next;
        gq->back->next = gq->front;

        return dequeued;
        //free(dequeued);
    }
    return NULL;
}

// creates a new student with the given sequence number
Student* createStudent(int sequence){
    Student* st = (Student*)malloc(sizeof(Student));
    st->sequenceNumber = sequence;
    st->next = NULL;

    return st;
}
// create a new garage with the 'nodeCount' number of students, 'th' threshold for the 
// first round of elimination, 'gNum' for the garage number, and 'k' for the kth student
// to eliminate 
GarageQueue* createGarage(int nodeCount, int k, int th, int gNum){
    GarageQueue* gq = (GarageQueue*)malloc(sizeof(GarageQueue));
    gq->front = NULL;
    gq->back = NULL;
    gq->k = k;
    gq->th = th;
    gq->gNum = gNum;

    gq->nodeCount = nodeCount;
    // initialize the queue in the garage
    createReverseCircle(gq);    

    return gq;
}

// enqueue students into a circular linked list queue in descending order
void createReverseCircle(GarageQueue* gq){
    int n = gq->nodeCount;
    gq->nodeCount = 0;
    for(int i = n-1; i>=0; i--){
        enqueue(gq, i+1);
    }
}
// reverses the order of the circular queue.
// essentially reverses the direction that the pointers are pointing.
// the first node will point to the previous node (last node), the next node will point to 
// this previous node, and so on. 
void rearrangeCircle(GarageQueue* gq){
    if(!isempty(gq)){
        Student* next = gq->front->next; // the next node to change pointer direction of
        Student* prev = gq->back; // the node one space behind the current node
        Student* curr = gq->front; // the current node to change the pointer direction

        // reverse the order of the front and back pointer in the queue
        gq->front = gq->back;
        gq->back = curr;

        // if curr->next points to the previous node, then we must be back at the 
        // previously first (now last) node
        while(curr->next != prev){
            curr->next = prev; // reverse direction of curr->next pointer
            prev = curr;
            curr = next;
            next = next->next;
        }
    }
}
// display the sequence numbers of the students in the garage queue
void display(const GarageQueue* gq){
    Student* temp = gq->front;
    printf("%d", gq->gNum);
    for(int i = 0; i<gq->nodeCount-1; i++){
        printf(" %d", temp->sequenceNumber);
        temp = temp->next;
    }
    printf(isempty(gq) ? "\n" : " %d\n", temp->sequenceNumber);
}

// the first phase of eliminating students from the competition
// skips pasts k-1 students and then eliminates the kth student from the 
// competition. repeats this until the number of students is equals to the 
// threshold 'th'
void phaseOneElimination(GarageQueue* gq){
    Student* km1Stu = gq->back; // the kth - 1 student

    while(gq->nodeCount > gq->th){
        for(int i = 0; i<gq->k-1; i++){
            km1Stu = km1Stu->next;
        }
        
        Student* kthStu = km1Stu->next;
        int seq = kthStu->sequenceNumber;
        if(kthStu == gq->front){
            gq->front = gq->front->next;
        }
        else if(kthStu == gq->back){
            gq->back = km1Stu;
        }

        km1Stu->next = km1Stu->next->next;
        free(kthStu);
        gq->nodeCount--;
        printf("Student# %d eliminated\n", seq);
    }
}

// returns a pointer to an array of the garage numbers of the nonempty garages.
// the garage numbers should correspond to their index + 1
int* getNonemptyGNums(GarageQueue** garages, int garageCount){
    int* gNums = (int*)malloc(sizeof(int)*garageCount);
    int gIndex = 0;
    int stuCount = 0;
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL){
            gNums[gIndex] = garages[i]->gNum;
            gIndex++;
        }
    }
    return gNums;
}

// removes the student with the highest sequence in all of the garages
// 'garages' is the pointer to an array of garage queues 
// 'garageCount' is the total number of nonempty garages 
// 'garageNums' is an array of the indices + 1 for the garages, assuming that the garage numbers are in ascending order
void deleteHighestSeqStudent(GarageQueue** garages, int garageCount, int* garageNums){    
    int maxSeq = -1;
    GarageQueue* maxStuGarage;
    for(int i = 0; i<garageCount; i++){
        GarageQueue* currGarage = garages[garageNums[i]-1];
        if(!isempty(currGarage)){
            Student* currStu = peek(currGarage);
            if(maxSeq < currStu->sequenceNumber){
                maxSeq = currStu->sequenceNumber;
                maxStuGarage = currGarage;
            }
            else if(maxSeq == currStu->sequenceNumber && maxStuGarage->gNum > currGarage->gNum){
                maxStuGarage = currGarage;
            }
        }
    }
    printf("Eliminated student %d from group for garage %d\n", maxSeq, maxStuGarage->gNum);
    free(dequeue(maxStuGarage)); 
}

// phase two eliminates the student with the highest sequence number among all of the
// garages, continuing until one student, the winner, remains
void phaseTwoElimination(GarageQueue** garages, int garageCount){
    int stuCount = 0; // total number of students in all of the garages
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL)
            stuCount += garages[i]->nodeCount;
    }
    
    int* gNums = getNonemptyGNums(garages, garageCount);
    while(stuCount > 1){
        deleteHighestSeqStudent(garages, garageCount, gNums);
        stuCount--;
    }

    for(int i = 0; i<garageCount; i++){
        GarageQueue* g = garages[gNums[i]-1];
        if(!isempty(g)){
            printf("\nStudent %d from the group for garage %d is the winner!\n",
                    peek(g)->sequenceNumber, g->gNum);
            free(peek(g));
        }
        free(g);
    }

    free(gNums);
}

int main(){
    int garageCount;
    scanf("%d", &garageCount);
    GarageQueue* garages[MAX_GARAGES];
    
    // initialize the garage queues
    for(int i = 0; i<MAX_GARAGES; i++)
        garages[i] = NULL;
    for(int i = 0; i<garageCount; i++){
        int gNum, n, k, th;
        scanf("%d %d %d %d", &gNum, &n, &k, &th);
        garages[gNum-1] = createGarage(n, k, th, gNum);
    }

    printf("Initial status of nonempty queues\n");
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL){
            display(garages[i]);
        }
    }
    printf("\nAfter ordering status of nonempty queues\n");
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL){
            rearrangeCircle(garages[i]);
            display(garages[i]);
        }
    }
    
    printf("\nPhase1 elimination\n\n");
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL){
            printf("Group for Garage# %d\n", i+1);
            phaseOneElimination(garages[i]);
            puts("");
        }
    }

    printf("Phase2 elimination\n");
    phaseTwoElimination(garages, garageCount);

    return 0;
}