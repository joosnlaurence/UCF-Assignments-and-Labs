#include  <stdio.h>

int count = 0;
int binSearch(int* arr, int low, int high, int val){
    count++;
    int mid = (low+high)/2;
    if(low > high)
        return -1;
    else if(val < arr[mid]){
        return binSearch(arr, low, mid-1, val);
    }
    else if(val > arr[mid]){
        return binSearch(arr, mid+1, high, val);
    }
    else{
        //printf("%3d ", count);
        count = 0;
        return mid;
    }
}

void slmp_linear(int list1[], int list2[], int size1, int size2){
    int i = 0, j = 0;
    while(i < size1 && j < size2){
        if(list1[i] == list2[j]){
            printf("Common num: %d\n", list1[i]);
            i++;
            j++;
        }
        else if(list1[i] < list2[j])
            i++;
        else 
            j++;
    }
}
void slmp_linear_rec(int list1[], int list2[], int size1, int size2){
    if(size1 > 0 && size2 > 0){
        if(list1[size1-1] == list2[size2-1]){
            slmp_linear_rec(list1, list2, size1-1, size2-1);
            printf("Common num: %d\n", list1[size1-1]);
        }
        else if(list1[size1-1] > list2[size2-1])
            slmp_linear_rec(list1, list2, size1-1, size2);
        else 
            slmp_linear_rec(list1, list2, size1, size2-1);
            
    }
}

void printCommonNumbers(int list1[], int list2[], int size1, int size2){
    for(int i = 0; i<size1; i++){
        int index = binSearch(list2, 0, size2, list1[i]);
        if(index != -1)
            printf("Common num: %d\n", list1[i]);
    }
}

int main(){
    int size = 10;
    int l1[size];
    int l2[size/2];
    for(int i = 0; i<size; i++){
        l1[i] = i+1;
        if(i % 2 == 1)
            l2[i/2] = i+1;
    }
    for(int i = 0; i<size; i++){
        printf("%d ", l1[i]);
    }
    printf("\n");
    for(int i = 0; i<size/2; i++){
        printf("%d ", l2[i]);
    }
    printf("\n");

    // printCommonNumbers(l1, l2, size, size/2);
    slmp_linear_rec(l1, l2, size, size/2);
    return 0;
}