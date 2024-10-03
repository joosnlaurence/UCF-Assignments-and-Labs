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

// Memoization
void initDistMatrix(int numGarages, int points[][2], float distMatrix[2*MAX_EXPRESSWAYS][2*MAX_EXPRESSWAYS]){
    for(int i = 0; i<numGarages; i++){
        for(int j = i+1; j<numGarages; j++){
            distMatrix[i][j] = 
            distMatrix[j][i] = findDistance(points[i][0], points[j][0],
                                            points[i][1], points[j][1]);
        }
    }
}

// Combines memoization, permutation pairing, and pruning of the recursion tree
float findMinSumOfDist(int k, int numGarages, int used[], int points[][2]){
    static float distMatrix[2*MAX_EXPRESSWAYS][2*MAX_EXPRESSWAYS];
    static int distInit = 0;
    static int currentPairs[2*MAX_EXPRESSWAYS];
    static float minSum = -1;
    static float currSum = 0;

    // base case: if k == number of garages, return the distance between the two
    if(k >= numGarages){
        if(currSum < minSum || minSum == -1){
            minSum = currSum;
            for (int i = 0; i < numGarages; i++) {
                finalPermutation[i] = currentPairs[i];
            }
        }
        return minSum;
    }
    for(int i = 0; i<numGarages; i++){
        if(!used[i]){
            used[i] = 1;
            for(int j = i+1; j<numGarages; j++){
                if(!used[j]){
                    used[j] = 1;
                    currentPairs[k] = i;
                    currentPairs[k+1] = j;

                    if(!distInit){
                        distInit = 1;
                        initDistMatrix(numGarages, points, distMatrix);
                    }

                    float pairDist = distMatrix[i][j];
                    if(minSum == -1 || currSum + pairDist < minSum){
                        currSum += pairDist;
                        minSum = findMinSumOfDist(k+2, numGarages, used, points);
                    }

                    used[j] = 0;
                }
            }
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

        float minSum = findMinSumOfDist(0, numGarages, used, points);
        printf("%.3f\n", minSum);
        printMinGaragePairs(numGarages, points);
        free_mem(numGarages);
    }

    return 0;
}