#include <stdio.h>
#include <stdlib.h>

int triangle_number(int n){
    if(n == 1)
        return 1;
    else 
        return n + triangle_number(n-1);
}
int factorial(int n){
    if(n == 1)
        return 1;
    else
        return n * factorial(n-1);
}
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

int main(){
    int num = 10;
    char str[] = "Jason Laureano";

    // print_reverse(str, 15);
    // puts("");
    printf("%d\n", multiply(20, -100));
    
    return 0;
}