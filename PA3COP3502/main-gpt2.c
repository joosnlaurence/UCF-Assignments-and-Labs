#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_EXPRESSWAYS 8
#define MAX_GNAME_LEN 20

// The names of the garages
char** garages; 
// An array of the indices of the garages for which the permutation minimizes
// the sum of the distance between pairs of garages i and i+1.
int finalPermutation[2*MAX_EXPRESSWAYS]; 

float findDistance(int x1, int x2, int y1, int y2){
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void initDistMatrix(int numGarages, int points[][2], float distMatrix[2*MAX_EXPRESSWAYS][2*MAX_EXPRESSWAYS]){
    for(int i = 0; i<numGarages; i++){
        for(int j = i+1; j<numGarages; j++){
            distMatrix[i][j] = 
            distMatrix[j][i] = findDistance(points[i][0], points[j][0],
                                            points[i][1], points[j][1]);
        }
    }
}

float findMinPairing(int numGarages, int points[][2], int used[], int start){
    static float distMatrix[2*MAX_EXPRESSWAYS][2*MAX_EXPRESSWAYS];
    static int distInit = 0;
    static int currentPairs[2*MAX_EXPRESSWAYS];
    static float minSum = -1;
    static float currSum = 0;

    // Base case: when all garages are paired
    if (start >= numGarages) {
        if (currSum < minSum || minSum == -1) {
            minSum = currSum;
            // Copy currentPairs to finalPermutation when a new minimum is found
            for (int i = 0; i < numGarages; i++) {
                finalPermutation[i] = currentPairs[i];
            }
        }
        return minSum;
    }

    // Find two unused garages to pair up
    for (int i = 0; i < numGarages; i++) {
        if (!used[i]) {
            used[i] = 1;  // Mark garage i as used
            for (int j = i + 1; j < numGarages; j++) {
                if (!used[j]) {
                    used[j] = 1;  // Mark garage j as used
                    
                    // Add the pair to the currentPairs array
                    currentPairs[start] = i;
                    currentPairs[start + 1] = j;
                    
                    if(!distInit){
                        distInit = 1;
                        initDistMatrix(numGarages, points, distMatrix);
                    }

                    // Calculate the distance for the current pair
                    float pairDistance = distMatrix[i][j];
                    
                    // Prune if the current sum exceeds the best known minimum sum
                    if (minSum == -1 || currSum + pairDistance < minSum) {
                        // Recursively pair the remaining garages
                        currSum += pairDistance;
                        minSum = findMinPairing(numGarages, points, used, start + 2);
                    }

                    // Unmark garage j to try other combinations
                    used[j] = 0;
                }
            }
            // Unmark garage i to try other combinations
            used[i] = 0;
        }
    }
    return minSum;
}

void printMinGaragePairs(int numGarages, int points[numGarages][2]){    
    for(int i = 0; i<numGarages; i+=2){
        // int g = finalPermutation[i];
        // int gp1 = finalPermutation[i+1];
        // float dist = findDistance(points[g][0], points[gp1][0],
        //                         points[g][1], points[gp1][1]);
        float dist = findDistance(points[i][0], points[i+1][0],
                                points[i][1], points[i+1][1]);
        printf("(%s, %s, %.3f)\n", garages[i], garages[i+1], dist);
    }
}

void free_mem(int numGarages){
    for(int i = 0; i<numGarages; i++){
        free(garages[i]);
    }
    free(garages);
}

int main(){
    int n; // The number of expressways that we want to build
    scanf("%d", &n);
    int numGarages = 2*n;

    if(n >= 0){
        garages = (char**)malloc(sizeof(char*) * numGarages);
        int points[numGarages][2]; // [k,0] == xi; [k,1] == yi
        int used[numGarages]; // Track which indexes are fixed

        for(int i = 0; i<numGarages; i++){
            char gname[MAX_GNAME_LEN+1];
            scanf("%d %d %s", &points[i][0], &points[i][1], gname);

            garages[i] = (char*)malloc(sizeof(char) * (strlen(gname) + 1));
            strcpy(garages[i], gname);
            
            used[i] = 0;
        }
        // float distMatrix[2*MAX_EXPRESSWAYS][2*MAX_EXPRESSWAYS];
        // initDistMatrix(numGarages, points, distMatrix);

        float minSum = findMinPairing(numGarages, points, used, 0);
        
        printf("%.3f\n", minSum);
        printMinGaragePairs(numGarages, points);
        free_mem(numGarages);
    }

    return 0;
}