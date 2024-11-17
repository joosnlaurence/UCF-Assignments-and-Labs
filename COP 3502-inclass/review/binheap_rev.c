#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct binHeap{
    int* heaparray;
    int size;
    int capacity;
}binHeap;

typedef struct binTree{
    int data;
    struct binTree* left;
    struct binTree* right;
}binTree;

binHeap* initHeap(int capacity){
    binHeap* h = (binHeap*)malloc(sizeof(binHeap));
    h->heaparray = (int*)malloc(sizeof(int) * (capacity+1));
    h->size = 0;
    h->capacity = capacity;

    return h;
}

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void percolateUp(binHeap* heap, int index){
    if(index > 1){
        if(heap->heaparray[index/2] < heap->heaparray[index]){
            swap(&heap->heaparray[index/2], &heap->heaparray[index]);
            percolateUp(heap, index/2);
        }
    }
}

void insert(binHeap* heap, int val){
    if(heap->size < heap->capacity){
        heap->heaparray[++heap->size] = val;
        percolateUp(heap, heap->size);
    }
}

void printHeap(binHeap* h){
    int n = 1;
    while(n < h->size){
        for(int i = n; i < n + n && i <= h->size; i++){
            printf("%2d ", h->heaparray[i]);
        }
        printf("\n");
        n *= 2;        
    }
}

int main(){
    //srand(time(NULL));
    int cap = 30;
    binHeap* heap = initHeap(cap);
    for(int i = 1; i<=heap->capacity; i++){
        int n = rand() % 100 + 1;
        insert(heap, n);
    }
    printHeap(heap);

    return 0;
}
