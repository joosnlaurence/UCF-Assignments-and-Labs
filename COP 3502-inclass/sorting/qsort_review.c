#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int partition(int arr[], int lo, int hi){
    int i = rand() % (hi-lo + 1) + lo;
    swap(&arr[lo], &arr[i]);

    int pi = lo;
    lo++;

    while(lo <= hi){
        while(lo <= hi && arr[lo] <= arr[pi])
            lo++;
        while(lo <= hi && arr[hi] >= arr[pi])
            hi--;
        if(lo < hi)
            swap(&arr[lo], &arr[hi]);
    }
    swap(&arr[hi], &arr[pi]);
    return hi;
}

void quick_sort(int arr[], int l, int r){
    if(l < r){
        int k = partition(arr, l, r);

        quick_sort(arr, l, k-1);
        quick_sort(arr, k+1, r);
    }
}

int isSorted(int arr[], int size){
    for(int i = 0; i < size-1; i++){
        if(arr[i] > arr[i+1])
            return 0;
    }
    return 1;
}

int main(){
    srand(time(NULL));
    int size = 100;
    int arr[size];
    for(int i = 0; i<size; i++){
        arr[i] = rand() % (size * 10);
    }
    printf("Sorted: %s\n", isSorted(arr, size) ? "True":"False");
    quick_sort(arr, 0, size-1);
    printf("Sorted: %s\n", isSorted(arr, size) ? "True":"False");
    

    return 0;
}