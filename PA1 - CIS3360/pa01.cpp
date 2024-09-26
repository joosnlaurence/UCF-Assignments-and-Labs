/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Jason Laureano
| Language: c++
| To Compile: g++ -o pa01 pa01.cpp
| To Execute: c++ -> ./pa01 kX.txt pX.txt
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#define MAX_LENGTH 100000
using namespace std;

// Multiplies two matrices 
vector<vector<int>> multMatrices(const vector<vector<int>> &m1, const vector<vector<int>> &m2){
    if(m1[0].size() != m2.size())
        throw "Error: Incompatible matrix dimensions";

    int m1row = m1.size();
    int m1col = m1[0].size();
    int m2col = m2[0].size();
    vector<vector<int>> c(m1row, vector<int>(m2col, 0));
    
    for(int i = 0; i<m1row; i++){
        for(int j = 0; j<m2col; j++){
            for(int k = 0; k<m1col; k++){
                c[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return c;
}  

string hillCipher(const string &ptext, const vector<vector<int>> &key){
    if(key.size() <= 1)
        throw "Error: Key matrix is less than 2x2";
    else if(key.size() != key[0].size())
        throw "Error: Key matrix is not square";
    
    int numBlocks = ptext.length()/key.size();
    int blocksize = key.size();
    string ciphertext = ""; 
    vector<vector<int>> ptextMatrix(key.size(), vector<int>(1));

    for(int i = 0; i<numBlocks; i++){
        string block = ptext.substr(i*blocksize, blocksize);
        for(int j = 0; j<block.size(); j++){
            ptextMatrix[j][0] = block[j]-'a';
        }

        vector<vector<int>> cipherMatrix;
        try{
            cipherMatrix = multMatrices(key, ptextMatrix);
        } catch(string err){
            throw err;
        }
        for(int k = 0; k<cipherMatrix.size(); k++){
            ciphertext += (char)(cipherMatrix[k][0] % 26 + 'a');
        }
    }
    return ciphertext;
}

// Prints text that newlines after every lnWidth characters are printed.
void printText(const string &str, int lnWidth){
    int i;
    for(i = 0; i<(str.length() / lnWidth); i++)
        cout << str.substr(i*lnWidth, lnWidth) << '\n';
    if(str.length() % lnWidth != 0)
        cout << str.substr(i*lnWidth) << '\n';
}

// argv[1]=key, argv[2]=plaintext
int main(int argc, char* argv[]){
    // Get the name of the key and plaintext files 
    std::ifstream keyF{ argv[1] };
    if(!keyF) { 
        cerr << "Key file could not be opened\n";
        return 1;
    }
    std::ifstream ptextF{ argv[2] };
    if(!ptextF){
        cerr << "Plaintext file could not be opened\n";
        return 1;
    }
    // Insert the key data into a 2D array
    // 1 < n < 10
    int n; 
    keyF >> n;
    vector<vector<int>> keyMatrix(n, vector<int>(n));

    cout << "\nKey matrix:\n";
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            keyF >> keyMatrix[i][j];
            cout << setw(4) << right << keyMatrix[i][j];
        }
        cout << "\n";
    }    

    // Run through the plaintext character by character to format its input
    string plaintext;
    char ch;
    while(ptextF.get(ch)){
        if(isalpha(ch)){
            plaintext += tolower(ch);
        }
    }    
    // Pad the plaintext with x's as necessary
    for(int i = 0; i<plaintext.length() % n; i++){
        plaintext += 'x';
    }     

    int lineWidth = 80;
    cout << "\nPlaintext:\n";
    printText(plaintext, lineWidth);

    // Encrypt the plaintext using the key and the hill cipher
    string ciphertext;
    try{
        ciphertext = hillCipher(plaintext, keyMatrix);
    } catch(string &err){
        cerr << err << '\n';
        return 1;
    }
    cout << "\nCiphertext:\n";
    printText(ciphertext, lineWidth);

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