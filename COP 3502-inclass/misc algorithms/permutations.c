#include <stdio.h>
#define SIZE 3
void print(int *A, int n)
    {
    for(int i=0; i<n; i++)
        printf("%d ", A[i]);
        printf("\n");
}
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printperms(int* perm, int* used, int k, int n){
    if(k == n){
        print(perm, n);
        return;
    }
    for(int i=0; i<n; i++){
        if(!used[i]){
            used[i] = 1;
            perm[k] = i;

            printperms(perm, used, k+1, n);

            used[i] = 0;
        }
    }
}
int count = 0;
void printperms_rec(int arr[], int l, int r){
    if(l == r){
        count++;
        print(arr, r);
        return;
    }
    for(int i = l; i<r; i++){
        swap(&arr[i], &arr[l]);
        printperms_rec(arr, l+1, r);
        swap(&arr[i], &arr[l]);
    }
}


int main(void) {
    int perm[SIZE] = {0}; //to build and store the permutation
    int used[SIZE] = {0}; //tracking which index is used
    int arr[SIZE] = {0,1,2};
    // printperms(perm, used, 0, SIZE);
    printperms_rec(arr, 0, SIZE);
    printf("%d\n", count);
    return 0;
}