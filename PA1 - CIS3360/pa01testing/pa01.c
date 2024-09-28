/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Jason Laureano
| Language: c
| To Compile: gcc -o pa01 pa01.cpp
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
| Due Date: 9/29
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_PTEXT_LENGTH 10000

void multMatrices(int m1rows, int m1cols, int m1[m1rows][m1cols], 
                  int m2rows, int m2cols, int m2[m2rows][m2cols],
                  int result[m1rows][m2cols]) {
    // Ensure that the number of columns of A matches the number of rows of B
    if (m1cols != m2rows) {
        perror("Error: Incompatible matrix dimensions\n");
        return;
    }

    // Perform matrix multiplication
    for (int i = 0; i < m1rows; i++) {
        for (int j = 0; j < m2cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < m1cols; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
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
        
        int cipherMatrix[blockWidth][1];
        multMatrices(keysize, keysize, key, blockWidth, 1, ptextMatrix, cipherMatrix);

        for(int k = 0; k < keysize; k++){
            int currCh = blockWidth*i + k;
            ciphertext[currCh] = (char)(cipherMatrix[k][0] % 26 + 'a');
        }   
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
    int keyMatrix[n][n];

    printf("\nKey matrix:\n");
    for(int i = 0; i<n; i++){
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

    char* ciphertext = hillCipher(plaintext, n, keyMatrix);
    printf("\nCiphertext:\n");
    printText(ciphertext, lineWidth);
    free(ciphertext);

    fclose(keyF);
    fclose(ptextF);

    return 0;
}

/*=============================================================================
| I Jason Laureano (ja193947) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/