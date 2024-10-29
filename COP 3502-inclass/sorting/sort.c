#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// void merge(int arr[], int l, int m, int r){

// }

// void mergesort(int arr[], int l, int r){
//     if(r > l){
//         int m = (l+r)/2;
//         mergesort(arr, l, m);
//         mergesort(arr, m+1, r);
//         merge(arr, l, m, r);
//     }
// }

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

// int partition(int arr[], int l, int r){
//     int i = l + rand() % (r-l + 1); // choose random index as pivot
//     swap(&arr[i], &arr[l]);

//     int pi = l;
//     l++;

//     while(l <= r){
//         while(l <= r && arr[l] <= arr[pi])
//             l++;
//         while(l <= r && arr[r] >= arr[pi])
//             r--;
//         if(l < r)
//             swap(&arr[l], &arr[r]);
//     }

//     swap(&arr[r], &arr[pi]);
//     return r;
// }
int partition(int arr[], int l, int r){
    int i = l + rand() % (int)(r-l + 1); // choose random index as pivot
    swap(&arr[i], &arr[l]);

    int pi = l;
    l++;

    while(l <= r){
        while(l <= r && arr[l] <= arr[pi])
            l++;
        while(l <= r && arr[r] >= arr[pi])
            r--;
        if(l < r)
            swap(&arr[l], &arr[r]);
    }

    swap(&arr[r], &arr[pi]);
    return r;
}

void quicksort(int arr[], int lo, int hi){
    if(lo < hi){
        int k = partition(arr, lo, hi);

        quicksort(arr, lo, k-1);
        quicksort(arr, k+1, hi);
    }
}

int isSorted(int arr[], int size){
    for(int i = 0; i < size-1; i++){
        if(arr[i] > arr[i+1])
            return 0;
    }
    return 1;
}

void printArr(int arr[], int size){
    for(int i = 0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
#define SIZE 100

int main(){
    srand(time(NULL));
    int arr[SIZE];
    for(int i = 0; i<SIZE; i++)
        arr[i] = rand() % (int)(SIZE * 10);
    //printArr(arr, SIZE);
    printf("Sorted: %s\n", isSorted(arr, SIZE) ? "True":"False");
    quicksort(arr, 0, SIZE-1);
    //printArr(arr, SIZE);
    printf("Sorted: %s\n", isSorted(arr, SIZE) ? "True":"False");

    return 0;
}