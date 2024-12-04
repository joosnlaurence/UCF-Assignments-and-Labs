#include <stdio.h>

int lowestOneBit(int n){
    unsigned int mask = 1U;
    while((n & mask) == 0){
        mask = mask << 1;
    }
    return n & mask;
}
int highestOneBit(int n){
    unsigned int mask = 1U << 31;
    while((n & mask) == 0){
        mask = mask >> 1;
    }
    return n & mask;
}

int main(){
    int n = 80;
    printf("%d\n", lowestOneBit(n));
    printf("%d\n", highestOneBit(n));

    return 0;
}