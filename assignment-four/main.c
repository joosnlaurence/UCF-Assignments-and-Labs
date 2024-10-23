#include <stdio.h>
#include <math.h>
#define CLOSER -1
#define FARTHER 1

typedef struct coords{
    int x, y;
}coords;

coords personCoords;

coords* ReadData(){

}
int compareTo(coords* ptrPt1, coords* ptrPt2){
    int x1 = ptrPt1->x, x2 = ptrPt2->x;
    int y1 = ptrPt1->y, y2 = ptrPt2->y;
    if(x1 == x2 && y1 == y2) // if same points
        return 0;

    float distPt1 = sqrt(pow(x1 - personCoords.x, 2) + pow(y1 - personCoords.y, 2));
    float distPt2 = sqrt(pow(x2 - personCoords.x, 2) + pow(y2 - personCoords.y, 2));

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

void binSearch();

void wrapper(coords* gCoords, int n, int threshold);

int main(){
    coords c1;
    c1.x = 1;
    c1.y = 0;
    coords c2;
    c2.x = 0;
    c2.y = 1;
    personCoords.x = 10;
    personCoords.y = 10;

    printf("%d\n", compareTo(&c1, &c2));

    return 0;
}