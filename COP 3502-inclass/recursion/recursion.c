#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int triangle_number(int n){
    if(n == 1)
        return 1;
    else 
        return n + triangle_number(n-1);
}
// int factorial(int n){
//     if(n == 1)
//         return 1;
//     else
//         return n * factorial(n-1);
// }
int fibonacci(int n){
    if(n <= 1)
        return n;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}
#define TIP_RATE 0.15
void tip_chart(int first, int last){
    if( !(first > last) ){
        printf("For a meal of $%d, you should tip $%.2lf\n",
                        first, first*TIP_RATE);
        tip_chart(first + 1, last);
    }
}
void print_reverse(char str[], int len){
    // if(len == 1)
    //     printf("%c\n", str[0]);
    // else{
    //     printf("%c", str[len-1]);
    //     print_reverse(str, len-1);
    // }
    if( !(len == 0) ){
        printf("%c", str[len-1]);
        print_reverse(str, len-1);
    }
}
int multiply(int n1, int n2){
    if(n2 == 0 || n1 == 0)
        return 0;
    else if(n2 < 0)
        return -multiply(n1, -n2);
    else if(n1 < 0)
        return -multiply(-n1, n2);
    else
        return n1 + multiply(n1, n2-1);
}

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod){
    if(n == 1){
        printf("\nMove disk 1 from rod %c to rod %c", from_rod, to_rod);
        return;
    }
    towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
    printf("\nMove disk %d from rod %c to rod %c", n, from_rod, to_rod);
    towerOfHanoi(n-1, aux_rod, to_rod, from_rod);
}

int count = 0;
unsigned long long fastPower(unsigned long long base, unsigned long long exponent){
    if(exponent == 0){
        return 1;
    }
    else if(exponent % 2 == 0){
        count++;
        return fastPower(base*base, exponent/2);
    }
    else{
        count++;
        return base*fastPower(base*base, exponent/2);
    }
   
}

void swap(char* c1, char* c2){
    char temp = *c2;
    *c2 = *c1;
    *c1 = temp;
}

void findPermutations(char* str, int leftmost, int rightmost){
    if(leftmost == rightmost)
        printf("%s\n", str);
    else{
        for(int i = leftmost; i <= rightmost; i++){
            swap(&str[leftmost], &str[i]);
            findPermutations(str, leftmost+1, rightmost);
            swap(&str[leftmost], &str[i]); //swap back
        }
    } 
}

int factorial(int n){
    if(n <= 0){
        return 1;
    }
    else{
        return n*factorial(n-1);
    }
}



int main(){
    int n;
    scanf("%d", &n);
    printf("%d! = %d\n", n, factorial(n));



    // printf("Enter a value (2-10): ");
    // int n; // number of disks
    // scanf("%d", &n);
    // if(n >= 2 && n <= 10)
    //     towerOfHanoi(n, 'A', 'C', 'B');
    // else 
    //     printf("Invalid value\n");
    // puts("");
    // int base = 2;
    // for(int i = 0; i<=20; i++){
    //     printf("fastPower(%d^%d): %llu\n", base, i, fastPower(base, i));
    //     printf("number of multiplications: %d\n", count);
    //     count = 0;
    // }
    // printf("Enter a word: ");
    // char ch[] = "doug";
    // findPermutations(ch, 0, strlen(ch)-1);
    return 0;
}