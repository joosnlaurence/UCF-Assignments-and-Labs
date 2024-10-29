#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMARRAYS 6
#define MAXVAL 1000000

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void selection_sort(int arr[], int size){
    for(int i = 0; i<size; i++){
        int minI = i;
        for(int j = i; j<size-1; j++){
            if(arr[j+1] < arr[minI])
                minI = j+1;
        }
        swap(&arr[minI], &arr[i]);
    }
}
void bubble_sort(int arr[], int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size-i-1; j++){
            if(arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
        }
    }
}
void insertion_sort_full(int arr[], int size){
    for(int i = 1; i<size; i++){
        int sort = arr[i];
        int k = i;
        while(k > 0 && arr[k-1] > sort){
            arr[k] = arr[k-1];
            k--;
        }
        arr[k]= sort;
    }
}
void insertion_sort_range(int arr[], int l, int r){
    for(int i = l+1; i<=r; i++){
        int sort = arr[i];
        int k = i;
        while(k > l && arr[k-1] > sort){
            arr[k] = arr[k-1];
            k--;
        }
        arr[k] = sort;
    }
}
void merge(int arr[], int l, int m, int r){
    int l_size = m - l + 1;
    int r_size = r - m;
    int* l_arr = (int*)malloc(sizeof(int) * l_size);
    int* r_arr = (int*)malloc(sizeof(int) * r_size);

    for(int i = 0; i<l_size; i++)
        l_arr[i] = arr[l + i];
    for(int j = 0; j<r_size; j++)
        r_arr[j] = arr[m+1 + j];

    int i = 0, j = 0;
    int k = l;
    while(i < l_size && j < r_size){
        if(l_arr[i] < r_arr[j]){
            arr[k] = l_arr[i];
            i++;
            k++;
        }
        else{
            arr[k] = r_arr[j];
            j++;
            k++;
        }
    }

    while(i < l_size){
        arr[k] = l_arr[i];
        i++;
        k++;
    }
    while(j < r_size){
        arr[k] = r_arr[j];
        j++;
        k++;
    }
    free(l_arr);
    free(r_arr);
}
void merge_sort(int arr[], int l, int r){
    if(r > l){
        int m = (r+l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
void merge_insertion_sort(int arr[], int l, int r){
    if( (r - l + 1) <= 25){
        insertion_sort_range(arr, l, r);
        return;
    }
    if(r > l){
        int m = (r+l) / 2;

        merge_insertion_sort(arr, l, m);
        merge_insertion_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

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

void printArr(int arr[], int size){
    for(int i = 0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void arrayCopy(int from[], int to[], int size)
{
    for(int j=0; j<size; j++)
        to[j] = from[j];
}
// Pre-condition: A is an array of size greater than or equal to size and
//                maxval is positive.
// Post-condition: A is filled with random integers in the range [1,maxval]
//                 from index 0 to index size-1.
void randArray(int A[], int size, int maxval) {
     // Fill each array slot in question with a random value in the designated range.
     for (int i=0; i<size; i++)
         A[i] = rand()%maxval + 1;
}
long timediff(clock_t t1, clock_t t2){
    long elapsed = ((double)t2-t1)/CLOCKS_PER_SEC * 1000;
    return elapsed;
}

int main(){
    srand(time(NULL));
    // Different sizes to test the sort.
    int sizes[NUMARRAYS] = {10000, 20000, 30000, 40000, 50000, 60000};

    int* originalArray; //to keep the original array unchanged so that we can use it for various algorithms.
    int* sortedArray; //We will mainly pass this one to all the function.
    int i, j;
    clock_t start, end;

    // Loop through trying each size.
    for (i=0; i<NUMARRAYS; i++) {

        // Allocate the space for the array and fill it.
        originalArray = (int*)malloc(sizeof(int)*sizes[i]);
        sortedArray = (int*)malloc(sizeof(int)*sizes[i]);

        randArray(originalArray, sizes[i], MAXVAL);

        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        bubble_sort(sortedArray, sizes[i]);
        end = clock();
        long elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Bubble sort.\n", sizes[i], elapsed);

        //the sorted array got sorted. So, we are copying the data from original array to sorted array again
        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        insertion_sort_full(sortedArray, sizes[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Insertion sort.\n", sizes[i], elapsed);

        // Repeat for selection_sort
        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        selection_sort(sortedArray, sizes[i]);
        end = clock();
        elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Selection sort.\n", sizes[i], elapsed);

        // Repeat for merge_sort without insertion
        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        merge_sort(sortedArray, 0, sizes[i]-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Merge sort.\n", sizes[i], elapsed);

        //Repeat for quick_sort
        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        quicksort(sortedArray, 0, sizes[i]-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Quick sort.\n", sizes[i], elapsed);

        // Repeat for merge_insertion_sort
        arrayCopy(originalArray, sortedArray, sizes[i]);
        start = clock();
        merge_insertion_sort(sortedArray, 0, sizes[i]-1);
        end = clock();
        elapsed = timediff(start, end);
        printf("Sorting %d values took %ld ms for Merge Insertion sort.\n", sizes[i], elapsed);

        free(sortedArray);
        free(originalArray);
        printf("\n");
    }
    system("PAUSE");
    
    return 0;
}