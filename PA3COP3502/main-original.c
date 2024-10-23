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

float findMinSumOfDist(int* perm, int* used, int k, int numGarages, int points[numGarages][2], float minSum){
 
    // base case: if k == number of garages, return the distance between the two
    if(k == numGarages){
        float currSum = 0;
        for(int i = 0; i<numGarages; i+=2){
            currSum += findDistance(points[perm[i]][0], points[perm[i+1]][0],
                                points[perm[i]][1], points[perm[i+1]][1]);
            
        }

        if(minSum == -1 || currSum < minSum){
            minSum = currSum;
            for(int k = 0; k<numGarages; k++){
                    finalPermutation[k] = perm[k];
            }
        }
        return minSum;
    }
    for(int i = 0; i<numGarages; i++){
        if(!used[i]){
            used[i] = 1;
            perm[k] = i;
            
            minSum = findMinSumOfDist(perm, used, k+1, numGarages, points, minSum);

            used[i] = 0;
        }
    }
    return minSum;
}   

void printMinGaragePairs(int numGarages, int points[numGarages][2]){    
    for(int i = 0; i<numGarages; i+=2){
        int g = finalPermutation[i];
        int gp1 = finalPermutation[i+1];
        float dist = findDistance(points[g][0], points[gp1][0],
                                points[g][1], points[gp1][1]);
        printf("(%s, %s, %.3f)\n", garages[g], garages[gp1], dist);
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

    if(n >= 0){
        garages = (char**)malloc(sizeof(char*) * 2*n);
        int points[2*n][2]; // [k,0] == xi; [k,1] == yi
        int perm[2*n]; // Hold the current permutation
        int used[2*n]; // Track which indexes are fixed

        for(int i = 0; i<2*n; i++){
            char gname[MAX_GNAME_LEN+1];
            scanf("%d %d %s", &points[i][0], &points[i][1], gname);

            garages[i] = (char*)malloc(sizeof(char) * (strlen(gname) + 1));
            strcpy(garages[i], gname);
            
            perm[i] = 0;
            used[i] = 0;
        }

        float minSum = findMinSumOfDist(perm, used, 0, 2*n, points, -1);
        printf("%.3f\n", minSum);
        printMinGaragePairs(2*n, points);
        free_mem(2*n);
    }

    return 0;
}