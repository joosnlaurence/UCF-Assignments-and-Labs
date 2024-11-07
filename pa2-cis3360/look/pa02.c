/*============================================================================
| Assignment: pa02 - 8, 16, & 32 bit checksums
|
| Author: Hamid Yassin
| Language: c
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 kX.txt pX.txt
|
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
| Due Date: 11/03/2024
+===========================================================================*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Validate input arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <checksum size>\n", argv[0]);
        return 1;
    }
    
    char *filename = argv[1];
    int checksumSize = atoi(argv[2]);
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // Open file for reading
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Initialize variables
    unsigned long checksum = 0;
    int charCount = 0;
    int lineLength = 0;
    int ch;

    putchar('\n');

    // Read and print 80-char lines, accumulate checksum
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        charCount++;
        lineLength++;

        // Print a newline after every 80 characters
        if (lineLength % 80 == 0) {
            putchar('\n');
        }
    }
    // Pad with 'X' if necessary for alignment
    int padChars = ((checksumSize / 8) - (charCount % (checksumSize / 8))) % (checksumSize/8);
    charCount += padChars;
    while(padChars > 0){
        printf("%c", 'X');
        padChars--;
    } 
    printf("\n");   

    // Rewind file to calculate the checksum with blocks
    rewind(file);
    if (checksumSize == 8) {
        // 8-bit checksum: add each character's value
        while ((ch = fgetc(file)) != EOF) {
            checksum += ch;
            checksum &= 0xFF;  // Mask to keep lower 8 bits
        }
    } else if (checksumSize == 16) {
        // 16-bit checksum: process two characters at a time
        while ((ch = fgetc(file)) != EOF) {
            int nextChar = fgetc(file);
            unsigned short block = (ch << 8) | (nextChar == EOF ? 'X' : nextChar);
            checksum += block;
            checksum &= 0xFFFF;  // Mask to keep lower 16 bits
        }
    } else if (checksumSize == 32) {
        // 32-bit checksum: process four characters at a time
        while ((ch = fgetc(file)) != EOF) {
            int nextChar1 = fgetc(file);
            int nextChar2 = fgetc(file);
            int nextChar3 = fgetc(file);
            unsigned long block = (ch << 24) |
                                  ((nextChar1 == EOF ? 'X' : nextChar1) << 16) |
                                  ((nextChar2 == EOF ? 'X' : nextChar2) << 8) |
                                  (nextChar3 == EOF ? 'X' : nextChar3);
            checksum += block;
            checksum &= 0xFFFFFFFF;  // Mask to keep lower 32 bits
        }
    }

    // Print checksum result
    printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, checksum, charCount);

    // Clean up
    fclose(file);
    return 0;
}








/*=============================================================================
| I Hamid Yassin (ha338829) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/