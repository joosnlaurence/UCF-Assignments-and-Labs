#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_PTEXT_LENGTH 10000

int** multMatrices(int m1rows, int m1cols, int m1[m1rows][m1cols], 
                  int m2rows, int m2cols, int m2[m2rows][m2cols]) {
    // Ensure that the number of columns of A matches the number of rows of B
    if (m1cols != m2rows) {
        perror("Error: Incompatible matrix dimensions\n");
        return NULL;
    }

    int** result = (int**)malloc(sizeof(int*)*m1rows);
    // Perform matrix multiplication
    for (int i = 0; i < m1rows; i++) {
        result[i] = (int*)malloc(sizeof(int)*m2cols);
        for (int j = 0; j < m2cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m1cols; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

char* hillCipher(const char* ptext, int keysize, int key[][keysize]){
    if(keysize <= 1){
        perror("Error: Key matrix is less than 2x2\n");
        return NULL;
    }

    int numBlocks = strlen(ptext) / keysize;
    int blockWidth = keysize;
    char* ciphertext = (char*)malloc(sizeof(char) * (strlen(ptext) + 1));
    int ptextMatrix[blockWidth][1];

    for(int i = 0; i < numBlocks; i++){
        char block[blockWidth];
        strncpy(block, ptext + i*blockWidth, blockWidth);
        for(int j = 0; j<blockWidth; j++)
            ptextMatrix[j][0] = block[j] - 'a';
        
        int** cipherMatrix = multMatrices(keysize, keysize, key, blockWidth, 1, ptextMatrix);

        for(int k = 0; k < keysize; k++){
            int currCh = blockWidth*i + k;
            ciphertext[currCh] = (char)(cipherMatrix[k][0] % 26 + 'a');
            free(cipherMatrix[k]);
        }   
        free(cipherMatrix);
    }
    ciphertext[blockWidth * numBlocks] = '\0'; 
    return ciphertext;
}

void printText(const char* str, int lnWidth){
    int i;
    int len = strlen(str);
    for(i = 0; i < (len / lnWidth); i++)
        printf("%.*s\n", lnWidth, str + lnWidth*i);
    if(len % lnWidth != 0)
        printf("%.*s\n", len%lnWidth, str + lnWidth*i);
}

int main(int argc, char* argv[]){
    FILE* keyF = fopen(argv[1], "r");
    if(!keyF) { 
        printf("Key file could not be opened\n");
        return -1;
    }
    FILE* ptextF = fopen(argv[2], "r");
    if(!ptextF){
        printf("Plaintext file could not be opened\n");
        return -1;
    }

    int n;
    fscanf(keyF, "%d", &n);
    //int** keyMatrix = (int**)malloc(sizeof(int*) * n);
    int keyMatrix[n][n];

    printf("\nKey matrix:\n");
    for(int i = 0; i<n; i++){
        //keyMatrix[i] = (int*)malloc(sizeof(int) * n);
        for(int j = 0; j<n; j++){
            fscanf(keyF, "%d", &keyMatrix[i][j]);
            printf("%4d", keyMatrix[i][j]);
        }
        puts("");
    }  

    char plaintext[MAX_PTEXT_LENGTH+1];
    int currCh = 0;
    char ch;
    while(( ch = fgetc(ptextF) ) != EOF){
        if(isalpha(ch)){
            plaintext[currCh] = tolower(ch);
            currCh++;
        }
    }
    int padLen = n - currCh % n;
    for(int i = 0; i <  padLen; i++)
        plaintext[currCh++] = 'x';
    plaintext[currCh] = '\0';

    int lineWidth = 80;
    printf("\nPlaintext:\n");
    printText(plaintext, lineWidth);

    //char ciphertext[strlen(plaintext)+1];
    char* ciphertext = hillCipher(plaintext, n, keyMatrix);
    printf("\nCiphertext:\n");
    printText(ciphertext, lineWidth);
    free(ciphertext);

    fclose(keyF);
    fclose(ptextF);

    return 0;
}