#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int arr[], int size){
    for(int i = 1; i < size; i++){
        int k = i;
        int hand = arr[k];
        while(k > 0 && arr[k-1] > hand){
            arr[k] = arr[k-1];
            k--;
        }
        arr[k] = hand;
    }
}

void print(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    srand(time(NULL));
    int size = 10;
    int arr[size];
    for(int i = 0; i < size; i++){
        arr[i] = rand() % (10 * size) + 1;
    }
    
    print(arr, size);
    insertion_sort(arr, size);
    print(arr, size);

    return 0;
}