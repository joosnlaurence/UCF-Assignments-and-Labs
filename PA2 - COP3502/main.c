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

Student* peek(const GarageQueue* gq){
    if(gq != NULL)
        return gq->front;
    return NULL;
}
int isempty(const GarageQueue* gq){
    if(gq == NULL)
        return -1;
    return gq->nodeCount == 0;
}

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
void dequeue(GarageQueue* gq){
    if(!isempty(gq)){
        gq->nodeCount--;
        Student* dequeued = gq->front;
        gq->front = dequeued->next;
        gq->back->next = gq->front;

        free(dequeued);
    }
}

Student* createStudent(int sequence){
    Student* st = (Student*)malloc(sizeof(Student));
    st->sequenceNumber = sequence;
    st->next = NULL;

    return st;
}
GarageQueue* createGarage(int nodeCount, int k, int th, int gNum){
    GarageQueue* gq = (GarageQueue*)malloc(sizeof(GarageQueue));
    gq->front = NULL;
    gq->back = NULL;
    gq->k = k;
    gq->th = th;
    gq->gNum = gNum;

    gq->nodeCount = nodeCount;
    createReverseCircle(gq);    

    return gq;
}

void createReverseCircle(GarageQueue* gq){
    int n = gq->nodeCount;
    gq->nodeCount = 0;
    for(int i = n-1; i>=0; i--){
        enqueue(gq, i+1);
    }
}
void rearrangeCircle(GarageQueue* gq){
    if(gq != NULL){
        Student* next = gq->front->next;
        Student* prev = gq->back;
        Student* curr = gq->front;

        gq->front = gq->back;
        gq->back = curr;

        while(curr->next != prev){
            curr->next = prev;
            prev = curr;
            curr = next;
            next = next->next;
        }
    }
}
void display(const GarageQueue* gq){
    Student* temp = gq->front;
    printf("%d ", gq->gNum);
    if(temp != NULL){
        do{
            printf("%d ", temp->sequenceNumber);
            temp = temp->next;
        }while(temp != NULL && temp->next != gq->front);
    }
    printf("%d\n", temp->sequenceNumber);
}

void phaseOneElimination(GarageQueue* gq){
    Student* temp = gq->back;

    while(gq->nodeCount > gq->th){
        for(int i = 0; i<gq->k-1; i++){
            temp = temp->next;
        }
        Student* t = temp->next;
        int seq = t->sequenceNumber;
        if(t == gq->front){
            gq->front = gq->front->next;
            free(t);
            gq->back->next = gq->front;
        }
        else if(t == gq->back){
            gq->back = temp;
            free(t);
            gq->back->next = gq->front;
        }
        else{
            temp->next = temp->next->next;
            free(t);
        }
        gq->nodeCount--;
        printf("Student# %d eliminated\n", seq);
    }
}

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

void deleteHighestSeqStudent(GarageQueue** garages, int garageCount){
    int* gNums = getNonemptyGNums(garages, garageCount);
    
    int maxSeq = -1;
    GarageQueue* maxStuGarage;
    Student* maxStu;
    for(int i = 0; i<garageCount; i++){
        GarageQueue* currGarage = garages[gNums[i]-1];
        if(currGarage->nodeCount > 0){
            Student* currStu = peek(currGarage);
            if(maxSeq < currStu->sequenceNumber){
                maxSeq = currStu->sequenceNumber;
                maxStu = currStu;
                maxStuGarage = currGarage;
            }
            else if(maxSeq == currStu->sequenceNumber && maxStuGarage->gNum > currGarage->gNum){
                maxStuGarage = currGarage;
                maxStu = currStu;
            }
        }
    }
    printf("Eliminated student %d from group for garage %d\n", maxSeq, maxStuGarage->gNum);
    dequeue(maxStuGarage);

    free(gNums);
}

void phaseTwoElimination(GarageQueue** garages, int garageCount){
    int stuCount = 0;
    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL)
            stuCount += garages[i]->nodeCount;
    }
    
    while(stuCount > 1){
        deleteHighestSeqStudent(garages, garageCount);
        stuCount--;
    }

    for(int i = 0; i<MAX_GARAGES; i++){
        if(garages[i] != NULL && garages[i]->nodeCount == 1){
            GarageQueue* g = garages[i];
            printf("\nStudent %d from the group for garage %d is the winner!\n",
                    peek(g)->sequenceNumber, g->gNum);
            free(peek(g));
            free(g);
        }
        else
            free(garages[i]);
    }
}

int main(){
    int garageCount;
    scanf("%d", &garageCount);
    GarageQueue* garages[MAX_GARAGES];

    
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