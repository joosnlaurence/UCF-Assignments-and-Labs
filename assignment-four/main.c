#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define CLOSER -999
#define FARTHER 999

typedef struct coords{
    int x, y;
}coords;

coords personCoords;

// Return the distance between the point and the user's coordinates
float calcDist(int x, int y){
    return sqrt(pow(x - personCoords.x, 2) + pow(y - personCoords.y, 2));
}

coords* ReadData(int* numG, int* s, int* t){
    scanf("%d %d", &personCoords.x, &personCoords.y);

    scanf("%d %d %d", numG, s, t);

    coords* c = (coords*)malloc(sizeof(coords) * (*numG));
    for(int i = 0; i < *numG; i++){
        scanf("%d %d", &c[i].x, &c[i].y);
    }

    return c;
}
/* Return -999 if point 1 is closer to the user than point 2
   Return 999 otherwise 
*/
int compareTo(coords* ptrPt1, coords* ptrPt2){
    int x1 = ptrPt1->x, x2 = ptrPt2->x;
    int y1 = ptrPt1->y, y2 = ptrPt2->y;
    if(x1 == x2 && y1 == y2) // if same points
        return 0;

    float distPt1 = calcDist(x1, y1);
    float distPt2 = calcDist(x2, y2);

    if(distPt1 < distPt2)
        return CLOSER;
    else if(distPt1 > distPt2)
        return FARTHER;
    else{ // same distance from person but distinct points
        if(x1 != x2) 
            return x1 < x2 ? CLOSER : FARTHER;
        else
            return y1 < y2 ? CLOSER : FARTHER;
    }
}

int bin_search(coords* gArr, int n, int px, int py){
    int l = 0, r = n;
    int val = calcDist(px, py);
    while(l <= r){
        int mid = (r+l)/2;
        int x = gArr[mid].x, y = gArr[mid].y;
        float dist = calcDist(x, y);
        if(val < dist)
            r = mid - 1;
        else if(val > dist)
            l = mid + 1;
        else
            return mid;
    }
    return -1;
} 

void merge();
void merge_sort(coords* coords, int l, int r, int t);

void insertion_sort(coords* coords, int l, int r);

void wrapper(coords* gCoords, int n, int threshold);

void print_coords(coords* coords, int n){
    for(int i = 0; i < n; i++){
        printf("%d %d\n", coords->x, coords->y);
    }
}

int main(){
    int numGarages, numPoints, threshold;
    coords* c = ReadData(&numGarages, &numPoints, &threshold);
    //wrapper(c, numGarages, threshold);

    print_coords(c, numGarages);
    return 0;
}