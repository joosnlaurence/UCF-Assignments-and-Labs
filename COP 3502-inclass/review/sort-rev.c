#include <stdio.h>
#include <stdlib.h>


void swap(int* n1, int* n2){
    int temp = *n2;
    *n2 = *n1;
    *n1 = temp;
}

int partition(int* arr, int l, int r){
    int pi = (rand() % (r-l+1)) + l;
    swap(&arr[l], &arr[pi]);
    pi = l;
    l++;
    
    while(l <= r){
        while(l <= r && arr[l] <= arr[pi]){
            l++;
        }
        while(r >= l && arr[r] > arr[pi]){
            r--;
        }
        
        if(l < r){
            swap(&arr[l], &arr[r]);
        }
    }
    swap(&arr[pi], &arr[r]);

    return r;
}

void quicksort(int* arr, int l, int r){
    if(r > l){
        int k = partition(arr, l, r);

        quicksort(arr, k+1, r);
        quicksort(arr, l, k-1);
    }
}

int main(){
    
    int size = 1000;
    int arr[size];
    for(int i = 0; i<size; i++){
        arr[i] = rand() % 1000 + 1;
    }
    
    quicksort(arr, 0, size-1);

    for(int i = 0; i<size; i++){
        if(i % 10 == 0)
            printf("\n");
        printf("%3d ", arr[i]);
    }
    puts("");
    
    return 0;
}
