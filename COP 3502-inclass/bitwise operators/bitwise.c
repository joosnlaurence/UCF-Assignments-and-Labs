#include <stdio.h>

int main(){
    int n = 10;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int check = 22;
    for(int i = 0; i<(1<<n); i++){
        int sum = 0;
        for(int j = 0; j<n; j++){
            if( (i & (1<<j) ) != 0)
                sum += arr[j];
        }
        // printf("Sum: %d\n", sum);
        char binary[n+1];
        for(int k = 0; k<n; k++){
            binary[n-1-k] = ((i >> k) & 1) + '0';
        }
        binary[n] = '\0';
        if(sum == check)
            printf("For i=%s(%d), sum is %d\n", binary, i, check);
    }

    return 0;
}