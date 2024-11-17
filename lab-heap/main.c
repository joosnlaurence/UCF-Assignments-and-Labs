/* COP 3502C Lab 11
This program is written by: Jason Laureano */
#include <stdio.h>
#include "main.h"

int main(){
    int n;
    printf("How many entries? ");
    scanf("%d", &n);

    printf("Enter %d entries: ", n);
    int arr[n];
    for(int i = 0; i<n; i++){
        scanf("%d", arr + i);
    }

    isHeap_recursive(arr, 0, n)? printf("Recursive says Yes!\n"): printf("Recursive says No!\n");
    isHeap_iter(arr, n)? printf("Iterative says Yes!\n"): printf("Iterative says No!\n");

    return 0;
}

// i: Starting point of array
// n: Size of array
// Returns if arr is a minheap using recursion
int isHeap_recursive(int *arr, int i, int n){
    if(i >= n || n <= 0)
        return 1;

    if(2*i+1 < n && arr[2*i+1] < arr[i]){
        return 0;
    }
    if(2*i+2 < n && arr[2*i+2] < arr[i]){
        return 0;
    }

    return isHeap_recursive(arr, 2*i+1, n) && isHeap_recursive(arr, 2*i+2, n);
}

// n: Size of array
// Returns if arr is a minheap iteration 
int isHeap_iter(int *arr, int n){
    for(int i = 0; i<=(n-2)/2; i++){
        if(arr[2*i+1] < arr[i])
            return 0;
        if(2*i+2 < n && arr[2*i+2] < arr[i])
            return 0;
    }
    return 1;
}
