#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define CAP 20

/* Implement binary heap using an array
   Left child for ith node is at 2i, right is at 2i + 1
   Parent for ith node is at i/2*/

typedef struct binHeap{
    int* heaparray ;
    int capacity; // size of entire array 
    int size; // heap size
}binHeap;

binHeap* initHeap(int cap){
    binHeap* heap = (binHeap*)malloc(sizeof(binHeap));
    heap->capacity = cap;
    heap->heaparray = (int*)malloc(sizeof(int)*(cap + 1));
    heap->size = 0;

    return heap;
}

void swap(int* n1, int* n2){
    int temp = *n2;
    *n2 = *n1;
    *n1 = temp;
}

// void percolateUp(binHeap* h, int index){
//     int smallerParent = h->heaparray[index/2] < h->heaparray[index];
//     while(index/2 > 0 && smallerParent){
//         swap(&h->heaparray[index], &h->heaparray[index/2]);
//         index /= 2;
//         smallerParent = h->heaparray[index/2] < h->heaparray[index];
//     }
// }

void percolateUp(binHeap* h, int index){
    if(index > 1){
        int smallerParent = h->heaparray[index/2] < h->heaparray[index];
        if(smallerParent){
            swap(&h->heaparray[index], &h->heaparray[index/2]);
            percolateUp(h, index/2);
        }
    } 
}

// int insert(binHeap* h, int val){
//     if(h->capacity == h->size){
//         h->heaparray = (int*)realloc(h->heaparray, sizeof(int) * (h->capacity*2+1));
//         if(h->heaparray == NULL) return 0;
//
//         h->capacity *= 2;
//     }
//
//     int i = ++(h->size);
//     h->heaparray[i] = val;
//     percolateUp(h, i);
//    
//     return 1;
// }

int insert(binHeap* h, int val){
    if(h->size == h->capacity){
        h->heaparray = (int*)realloc(h->heaparray, sizeof(int) * (h->capacity*2+1));
        if(h->heaparray == NULL) return 0;

        h->capacity *= 2;
    }
    h->heaparray[++h->size] = val;
    percolateUp(h, h->size);

    return 1;
}

// void percolateDown(binHeap* h, int i){
//     if(i*2 + 1 <= h->size){
//         int maxChild = (h->heaparray[2*i] > h->heaparray[2*i+1]) ? 2*i : 2*i+1;
//         if(h->heaparray[maxChild] > h->heaparray[i]){
//             swap(&h->heaparray[maxChild], &h->heaparray[i]);
//             percolateDown(h, maxChild);
//         }
//     }
//     else if(i*2 == h->size){
//         if(h->heaparray[2*i] > h->heaparray[i])
//             swap(&h->heaparray[2*i], &h->heaparray[i]);
//     }
// }

void percolateDown(binHeap* h, int i){
    if(2*i+1 <= h->size){
        int left = h->heaparray[2*i];
        int right = h->heaparray[2*i+1];
        int max = (left > right) ? 2*i : 2*i+1;

        if(h->heaparray[i] < h->heaparray[max])
            swap(&h->heaparray[i], &h->heaparray[max]);

        percolateDown(h, max);
    }
    else if(2*i <= h->size){
        if(h->heaparray[i] < h->heaparray[2*i])
            swap(&h->heaparray[i], &h->heaparray[2*i]);
    }
}

/*
int removeMin(binHeap* h){
    int retval;

    if(h->size > 0){
        retval = h->heaparray[1];
        swap(&h->heaparray[1], &h->heaparray[h->size]);
        h->size--;

        percolateDown(h, 1);
        
        return retval;
    }

    return -1;
}*/

int removeMax(binHeap* h){
    int retval;

    if(h->size > 0){
        retval = h->heaparray[1];
        h->heaparray[1] = h->heaparray[h->size--];
        percolateDown(h, 1);

        return retval;
    }
}

void heapify(binHeap* h){
    for(int i = h->size/2; i > 0; i--){
        percolateDown(h, i);
    }
}

void printHeap(binHeap* h){
    int leftmostChild = 1;
    
    while(leftmostChild <= h->size){
        for(int i = leftmostChild; i<=leftmostChild*2-1 && i<=h->size; i++){
            printf("%d ", h->heaparray[i]); 
        }
        puts("");
        leftmostChild *= 2;      
    }
}

int main(){
    srand(time(NULL));
    int cap = 100;
    binHeap* heapPtr = initHeap(cap);

    int arr[cap];
    for(int i = 0; i<cap; i++){
        int val = rand() % (cap*10) + 1; 
        heapPtr->heaparray[i+1] = val;
        heapPtr->size++;
    }
    //printf("%d\n", heapPtr->size);
    
    heapify(heapPtr);
    printHeap(heapPtr); 
    for(int i = 1; i<=heapPtr->size; i++){
        printf("%d ", removeMax(heapPtr));
    }
    puts("");

    return 0;
}
