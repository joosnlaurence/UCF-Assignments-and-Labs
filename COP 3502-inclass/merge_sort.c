#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int mid, int r){
    if(r > l){
        int l_size = mid - l + 1;
        int r_size = r - mid;
        int *l_arr = (int*)malloc(l_size*sizeof(int));
        int *r_arr = (int*)malloc(r_size*sizeof(int));
        for(int i = 0; i < l_size; i++){
            l_arr[i] = arr[i + l];
        }
        for(int j = 0; j  < r_size; j++){
            r_arr[j] = arr[j + mid + 1];
        }

        int i = 0, j = 0;
        int k = l;
        while(i<l_size && j<r_size){
            if(l_arr[i] < r_arr[j]){
                arr[k] = l_arr[i];
                i++;
            }
            else{
                arr[k] = r_arr[j];
                j++;
            }
            k++;
        }

        while(i<l_size){
            arr[k] = l_arr[i];
            i++;
            k++;
        }
        while(j<r_size){
            arr[k] = r_arr[j];
            j++;
            k++;
        }
        free(l_arr);
        free(r_arr);
    }
}

void merge_sort(int arr[], int l, int r){
    if(r > l){
        int mid = (l+r)/2;
        merge_sort(arr, 0, mid);

        merge_sort(arr, mid+1, r);

        merge(arr, l, mid, r);
    }
}

void print(int* arr, int size){
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void selectionSort(int arr[], int n){
    int temp;
    for(int i = 0; i<n; i++){
        int minIndex = i;
        for(int k = i+1; k<n; k++){
            if(arr[minIndex] > arr[k]){
                minIndex = k;
            }
        }
        swap(&arr[i], &arr[minIndex]);
    }
}
void bubbleSort(int arr[], int n){
    for(int i = 0; i<n-1; i++){
        for(int k = 0; k < n-i-1; k++){
            if(arr[k] > arr[k+1]){
                swap(&arr[k], &arr[k+1]);
            }
        }
    }
}

int main(){
    int size = 10;
    srand(time(NULL));
    int arr[size];
    for(int i = 0; i<size; i++){
        arr[i] = rand()%100 + 1;
    }

    print(arr, size);
    // merge_sort(arr, 0, size-1);
    // selectionSort(arr, size);
    bubbleSort(arr, size);
    print(arr, size);

    return 0;
}