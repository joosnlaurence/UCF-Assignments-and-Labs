/*  Academic Integrity statement - “I Jason Laureano (ja193947) affirm that
    this program is entirely my own work and that I have neither developed my code with any
    another person, nor copied any code from any other person, nor permitted my code to be copied
    or otherwise used by any other person, nor have I copied, modified, or otherwise used programs
    created by others. I acknowledge that any violation of the above terms will be treated as
    academic dishonesty.”
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned int convert_to_unsigned_binary(char* string, int bit_size){
    unsigned int result = 0;
    int shamt = 8;
    int blockSize = bit_size/8;
    for(int i = 0; i<blockSize; i++){
        result = result << shamt;
        result += (unsigned int)string[i];
    }

    return result;
}

unsigned int byte_wide_checksum(char* string, int bit_size){
    int byteSize = bit_size/8;
    unsigned int bitmask = (1UL << bit_size) - 1;
    unsigned int checksum = 0;
    char block[byteSize];
    for(int i = 0; i<strlen(string); i += byteSize){
        for(int k = 0; k<byteSize; k++)
            block[k] = string[i+k];
        unsigned int blockSum = convert_to_unsigned_binary(block, bit_size);
        checksum = (checksum + blockSum) & bitmask;
    }

    return checksum;
}

char* readFile(FILE* f, int blockSize){
    fseek(f,0,SEEK_END);
    int textSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    int padSize = (blockSize - (textSize % blockSize)) % blockSize;

    char* text = (char*)malloc(textSize + padSize + 1);
    fread(text, sizeof(char), textSize, f);
    while(padSize > 0){
        padSize--;
        text[textSize++] = 'X';
    }
    text[textSize] = '\0';

    return text;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }
    
    FILE* inFile = fopen(argv[1], "r");
    if(inFile == NULL){
        fprintf(stderr, "File not found\n");
        return 1;
    }

    int bitSize = atoi(argv[2]);
    if(bitSize != 8 && bitSize != 16 && bitSize != 32){
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }
    int byteSize = bitSize / 8;

    char* text = readFile(inFile, byteSize);
    int len = strlen(text);

    unsigned int checksum = byte_wide_checksum(text, bitSize);
    
    for(int i = 0; i<len; i+=80){
        printf("\n%.80s", text + i);
    }
    printf("\n%2d bit checksum is %8x for all %4d chars\n",
             bitSize, checksum, len);

    fclose(inFile);
    free(text);

    return 0;
}