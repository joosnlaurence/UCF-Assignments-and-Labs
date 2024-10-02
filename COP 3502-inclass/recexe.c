#include <stdio.h>
#include <stdlib.h>

int fastPower(int n, int exponent){
    if(exponent == 0){
        return 1;
    }
    else if(exponent % 2 == 0){
        return fastPower(n*n, exponent/2);
    }
    else{
        return n*fastPower(n*n, exponent/2);
    }
}

int crazySum(int n){
    if(n == 1)
        return 1;
    else{
        return crazySum(n-1) + fastPower(n, n);
    }
}

unsigned long long factorial(unsigned long long n){
    if(n <= 0){
        return 1;
    }
    else{
        return n*factorial(n-1);
    }
}

int question3(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return question3(10*a+b%10, b/10);
}

void decimalToOctal(int d){
    if(d / 8  == 0){
        printf("%d", d);
    }
    else{
        decimalToOctal(d/8);
        printf("%d", d%8);
    }

}

// int zeros(int n)
// {
//     int res = 0;
//     while (n!=0)
//     {
//         res += n/5;
//         n /= 5;
//     }
//     return res;
// }

int zeros(int n){
    if(n == 0)
        return 0;
    else{
        return n/5 + zeros(n/5);
    }
}

int productDigits(int n){
    if(n / 10 == 0)
        return n;
    else{
        return (n%10) * productDigits(n/10);
    }
}

int weightedSum(int numbers[], int n){
    if(n == 0)
        return 0;
    else if(n == 1)
        return numbers[0];
    else{
        return numbers[n-1] * n + weightedSum(numbers, n-1);
    }
}

int isSorted(int* arr, int n){
    if( n < 2 )
        return 1;
    else if( arr[n-1] >= arr[n-2]){
        return isSorted(arr, n-1);
    }
    else 
        return 0;
} 

int binarySearch(int numbers[], int low, int high, int value){
    int curr = numbers[(low+high)/2];
    if(low > high){
        return -1;
    }
    else if( value == curr ){
        return (low+high)/2;
    }
    else if( value < curr ){
        high = (low+high)/2 - 1;
        return binarySearch(numbers, low, high, value);
    }
    else{ // value > curr
        low = (low+high)/2 + 1;
        return binarySearch(numbers, low, high, value);
    }
}

typedef struct node{
    int data;
    struct node* next;
}node;

node* createNode(int item){
    node* t = (node*)malloc(sizeof(node));
    t->data = item;
    t->next = NULL;
    return t;
}

node* insertAtEnd(node* head, int item){
    if(head == NULL){
        return createNode(item);
    }
    else if(head->next == NULL){
        head->next = createNode(item);
        return head;
    }
    else{
        head->next = insertAtEnd(head->next, item);
        return head;
    }
}

void printList(node* head){
    if(head != NULL){
        printf("%d ", head->data);
        printList(head->next);
    }
    else{
        printf("\n\n");
    }
}

node* deleteItem(node* head, int del){
    if(head != NULL && head->data != del){
        if(head->next != NULL && head->next->data == del){
            node* t = head->next;
            head->next = head->next->next;
            free(t);
            return head;
        }
        else{
            head->next = deleteItem(head->next, del);
            return head;
        }
    }
    else if(head != NULL && head->data == del){
        node* t = head->next;
        free(head);
        return t;
    }
    else{
        printf("%d NOT FOUND\n", del);
        return head;
    }
}

int main(){
    node* head = NULL;
    while(1){
        int n;
        scanf("%d", &n);
        if(n == 1){
            int ele;
            scanf("%d", &ele);
            head = insertAtEnd(head, ele);
            printList(head);
        }
        else if(n == 2){
            int ele;
            scanf("%d", &ele);
            head = deleteItem(head, ele);
            printList(head);
        }
        else{
            break;
        }
    }
    // int nums[] = {1,2,3,4,5,6,7,8,9};
    // int size = sizeof(nums)/sizeof(int);
    // while(1){
    //     int find;
    //     scanf("%d", &find);
    //     if( find == -1 ) break;
    //     printf("index: %d\n", binarySearch(nums, 0, size-1, find));
    // }
    
    // int nums[] = {1,2,3,5,4};
    // int size = sizeof(nums)/sizeof(int);
    // printf(isSorted(nums, size) ? "Sorted\n" : "Not Sorted\n");

    // int nums[] = {5,5,5,5,5};
    // int size = sizeof(nums)/sizeof(int);
    // printf("weightedSum: %d\n", weightedSum(nums, size));

    // int n;
    // scanf("%d", &n);
    // printf("%d\n", productDigits(n));

    // int n = 20;
    // printf("%d\n", zeros(n));
    // printf("%llu\n", factorial(n));
    // char oct[MAXSIZE];
    // for(int i = 0; i<100; i++){
    //     printf("%d in octal is ", i);
    //     decimalToOctal(i);
    //     puts("");        
    // }
    

    // printf("%d\n", question3(10, 12321));

    // int n, e;
    // scanf("%d %d", &n, &e);
    // printf("%d^%d = %d\n", n, e, fastPower(n,e));
    // int n;
    // scanf("%d", &n);
    // printf("crazySum(%d): %d\n", n, crazySum(n));

    return 0;
}