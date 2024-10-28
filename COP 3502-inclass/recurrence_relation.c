#include <stdio.h>


int power(int n, int e){
    if(e <= 0)
        return 1;
    if(e == 1)
        return n;
    if (e % 2 == 0)
        return power(n*n, e/2);
    else
        return power(n*n*n, e/2);
}
int main(){
    printf("%d\n", power(2,16));
    
    return 0;
}