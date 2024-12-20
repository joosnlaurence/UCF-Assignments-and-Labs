/* COP3502C: Assignment 3
    This program was created by Jason Laureano
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_GARAGES 16
#define MAX_GNAME_LEN 20

typedef struct Garage{
    char name[MAX_GNAME_LEN];
    int x, y;
}Garage;

Garage garages[MAX_GARAGES];

// An array of the indices of the garages for which the permutation minimizes
// the sum of the distance between pairs of garages i and i+1.
int finalPermutation[MAX_GARAGES]; 

float findDistance(int x1, int x2, int y1, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void initDistCache(int numGarages, float distCache[MAX_GARAGES][MAX_GARAGES]) {
    for (int i = 0; i < numGarages; i++) {
        for (int j = i+1; j < numGarages; j++) {
            float dist = findDistance(garages[i].x, garages[j].x, garages[i].y, garages[j].y);
            distCache[i][j] = distCache[j][i] = dist;
        }
    } 
}

/* 
 Recursively computes the smallest total sum of the distances between the garages.
 Each garage can only be connected in a pair, so it finds various permutations and compares
 their total sums with each other to get the smallest sum. 
 Also sets the finalPermutation array to have the indices of the garages in the permutation
 that minimizes the sum. 
*/
float findMinSumOfDist(int* perm, int* used, int k, int numGarages, float currSum){
    // The precomputed values of each possible distance
    static float distCache[MAX_GARAGES][MAX_GARAGES];
    static int initialized = 0;
    if(!initialized){
        initDistCache(numGarages, distCache);
        initialized = 1;
    }
    static float minSum = 1e9;

    // base case: If all of the garages are fixed, then check if the current Sum
    // is less than the min sum, and change min sum and finalPermutation as necessary
    if(k == numGarages){
        if(currSum < minSum){
            minSum = currSum;
            for(int k = 0; k<numGarages; k++){
                finalPermutation[k] = perm[k];
            }
        }
        return minSum;
    }
    
    // These nested loops helps avoid having to deal with redundant calculations
    for(int i = 0; i<numGarages; i++){
        if(!used[i]){
            used[i] = 1;
            for(int j = i+1; j<numGarages; j++){ 
                if(!used[j]){
                    used[j] = 1;
                    perm[k] = i;
                    perm[k+1] = j;
                    
                    float dist = distCache[i][j];
                    // If the next sum is greater than our min sum, no need to calculate
                    // the rest of the values for the recursion branch.
                    if(currSum + dist < minSum) 
                        minSum = findMinSumOfDist(perm, used, k+2, numGarages, currSum + dist);

                    used[j] = 0;
                }
            }
            used[i] = 0;
        }
    }
    return minSum;
}   

// Prints the garages in pairs that correspond to the order that they appeared in the input
void printMinGaragePairs(int numGarages){    
    int* used = (int*)calloc(numGarages, sizeof(int));
    for(int i = 0; i<numGarages; i++){
        if(used[i] == 0){
            int j = 0;
            while(finalPermutation[j] != i){
                j++;
            }
            int g = finalPermutation[j];
            int gp1 = finalPermutation[j+1];
            used[g] = used[gp1] = 1;
            float dist = findDistance(garages[g].x, garages[gp1].x,
                                  garages[g].y, garages[gp1].y);
            printf("(%s, %s, %.3f)\n", garages[g].name, garages[gp1].name, dist);
        }        
    }
    free(used);
}

int main(){
    int n; // The number of expressways that we want to build
    scanf("%d", &n);
    int numGarages = 2*n;

    if(n > 0){
        int perm[numGarages]; // Hold the current permutation
        int used[numGarages]; // Track which indexes are fixed

        // Initialize the garages with the given inputs and both perm and used arrays to zero
        for(int i = 0; i<numGarages; i++){
            char gname[MAX_GNAME_LEN+1];
            int x, y;
            scanf("%d %d %s", &x, &y, gname);

            garages[i].x = x;
            garages[i].y = y;
            strcpy(garages[i].name, gname);
            
            perm[i] = 0;
            used[i] = 0;
        }

        float minSum = findMinSumOfDist(perm, used, 0, numGarages, 0);
        printf("%.3f\n", minSum);
        printMinGaragePairs(numGarages);
    }

    return 0;
}