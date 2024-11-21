/* COP 3502C Programming Assignment 6
This program is written by: Your Full Name */
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 26
#define MAX_WORD_LEN 2000000

typedef struct dict{
    // Number of times the string represented by this node was added to dict
    int str_cnt;  
    // Number of words in dictionary that start with this string
    int prefix_cnt;
    // Max frequency of a child node among all child nodes for a given parent 
    int max_child_cnt; 

    struct dict* next[MAX_CHARS];
}dict;

dict* initDict(){
    dict* d = (dict*)malloc(sizeof(dict));
    d->str_cnt = 0;
    d->prefix_cnt = 0; 
    d->max_child_cnt = 0;
    for(int i = 0; i<MAX_CHARS; i++){
        d->next[i] = NULL;
    }

    return d;
}

/* Inserts a string of a given frequency into the dictionary*/
void insert(dict* d, char* str, int i, int freq){
    if(str[i] == '\0'){
        d->str_cnt += freq;
        d->prefix_cnt += freq;
        return;
    }

    char ch = str[i] - 'a';
    if(d->next[ch] == NULL){
        d->next[ch] = initDict();
    }

    insert(d->next[ch], str, i+1, freq);
    
    d->prefix_cnt += freq;
    
    // Update the held max child's frequency along the path of the string
    if(d->next[ch]->prefix_cnt > d->max_child_cnt){
        d->max_child_cnt = d->next[ch]->prefix_cnt;
    }
    
}

/* Returns a string of the characters most likely to appear next after a prefix.
 * If the prefix is not in the dictionary or the prefix has no subsequent chars 
 *  in the dictionary, then returns NULL*/
char* nextLikelyChars(dict* d, char* str){
    int size = 0;
    
    // First check to see if the prefix is in the dictionary
    while(str[size] != '\0'){
        if(d == NULL){
            return NULL;
        }
        char ch = str[size] - 'a';
        d = d->next[ch];

        size++;
    }
    
    char* maxFreqChars = (char*)malloc(MAX_CHARS);
    int maxFreq = 0;
    int maxCount = 0; // Represents the size of the next likely chars string
    
    // Check the frequency of each of the next characters.
    for(int i = 0; i<MAX_CHARS; i++){
        if(d->next[i] != NULL){
            if(maxFreq < d->next[i]->prefix_cnt){
                // If there is a greater max, then reset the next likely chars string
                maxFreq = d->next[i]->prefix_cnt;
                maxCount = 1;
                maxFreqChars[0] = i + 'a';
            }
            else if(d->next[i]->prefix_cnt == maxFreq){
                maxCount++;
                maxFreqChars[maxCount-1] = i + 'a';
            }
        }
    }
    if(maxCount != 0){
        // maxCount represents the number of chars most likely to appear next
        maxFreqChars = (char*)realloc(maxFreqChars, sizeof(char) * (maxCount+1));
        maxFreqChars[maxCount] = '\0';
        return maxFreqChars;   
    }
    else{
        free(maxFreqChars);
        return NULL;
    }
    
}

void free_mem(dict* d, int c){
    for(int i = 0; i<MAX_CHARS; i++){
        if(d->next[i] != NULL){
            free_mem(d->next[i], c+1);
        }
    }
    free(d);
}

int main(){
    dict* dictionary = initDict();

    int n;
    scanf("%d", &n);
    
    char wordBuffer[MAX_WORD_LEN];
    
    for(int i = 0; i<n; i++){
        int cmd;
        scanf("%d", &cmd);    
        if(cmd == 1){ // Insert string
            int frequency;
            scanf("%s%d", wordBuffer, &frequency);
            insert(dictionary, wordBuffer, 0, frequency);
        }
        else if(cmd == 2){ // Predict based on prefix
            scanf("%s", wordBuffer);
            char* nextChars = nextLikelyChars(dictionary, wordBuffer);
            if(nextChars != NULL){
                printf("%s\n", nextChars);
                free(nextChars);
            }
            else{
                puts("unrecognized prefix");
            }
        }
        else{
            printf("Err: Invalid command (%d)", cmd);
            break;
        }
    }
    free_mem(dictionary, 0);

    return 0;
}
