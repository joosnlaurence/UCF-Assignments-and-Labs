#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define CLOSER -999
#define FARTHER 999

typedef struct coords{
    int x, y;
    float distToPerson;
}coords;

coords personCoords;

/* Return the distance between the point and the user's coordinates 
   Was the idea I used for most of the time, so I'll keep it here*/
// float calcDist(int x, int y){
//     return sqrt(pow(x - personCoords.x, 2) + pow(y - personCoords.y, 2));
// }

/* Slightly optimized calculation for distance that removes the need for math.h
    Comparing the squared euclidean distances is enough for searching and sorting
*/
float calcDist(int x, int y){
    return (x - personCoords.x)*(x - personCoords.x) + 
           (y - personCoords.y)*(y - personCoords.y);
}

/* Read input and initialize the values for s (number of queries), t (threshold), 
   numG (number of Garages), and the coords for the array and person
*/
coords* ReadData(int* numG, int* s, int* t){
    scanf("%d %d", &personCoords.x, &personCoords.y);
    personCoords.distToPerson = 0;
    scanf("%d %d %d", numG, s, t);

    coords* c = (coords*)malloc(sizeof(coords) * (*numG));
    for(int i = 0; i < *numG; i++){
        scanf("%d %d", &c[i].x, &c[i].y);
        c[i].distToPerson = calcDist(c[i].x, c[i].y);
    }

    return c;
}

/* Return -999 (CLOSER) if first point is closer to the user than point 2
   Return 999 (FARTHER) if first point is farther than point 2
   Return 0 if the two points are the same 
*/
int compareTo(coords* ptrPt1, coords* ptrPt2){
    int x1 = ptrPt1->x, x2 = ptrPt2->x;
    int y1 = ptrPt1->y, y2 = ptrPt2->y;
    if(x1 == x2 && y1 == y2) // if same points
        return 0;

    float distPt1 = ptrPt1->distToPerson;
    float distPt2 = ptrPt2->distToPerson;

    if(distPt1 < distPt2)
        return CLOSER;
    else if(distPt1 > distPt2)
        return FARTHER;
    else{ // same distance from person but distinct points
    // Smaller x or y coordinate is considered closer
        if(x1 != x2) 
            return x1 < x2 ? CLOSER : FARTHER;
        else
            return y1 < y2 ? CLOSER : FARTHER;
    }
}

/* Uses binary search to look for the given coordinates in the coords array */
int bin_search(coords* garageCoords, int n, coords* val){
    int l = 0, r = n-1;
    while(l <= r){
        int mid = (r+l)/2;
        int result = compareTo(val, &garageCoords[mid]);
        // Val coordinate is closer to person than mid coordinate
        if(result == CLOSER) 
            r = mid - 1;
        // Val coordinate is farther from person than mid coordinate
        else if(result == FARTHER)
            l = mid + 1;
        else
            return mid;
    }
    return -1;
} 

/* Insertion sort used with merge sort to sort the subarrays of the coords array*/
void insertion_sort(coords* c, int l, int r){
    for(int i = l+1; i <= r; i++){
        int k = i;
        coords currCoord = c[k];
        while( k > l && compareTo(&currCoord, &c[k-1]) == CLOSER ){
            c[k] = c[k-1];
            k--;
        }
        c[k] = currCoord;
    }
}

/* Merges two sub arrays, using m as the index separating them */
void merge(coords* c, int l, int m, int r){
    int l_size = m - l + 1;
    int r_size = r - m;
    coords* l_arr = (coords*)malloc(sizeof(coords)*l_size);
    coords* r_arr = (coords*)malloc(sizeof(coords)*r_size);
    for(int i = 0; i < l_size; i++){
        l_arr[i].x = c[i + l].x;
        l_arr[i].y = c[i + l].y;
        l_arr[i].distToPerson = c[i + l].distToPerson;
    }
    for(int i = 0; i < r_size; i++){
        r_arr[i].x = c[i + m + 1].x;
        r_arr[i].y = c[i + m + 1].y;
        r_arr[i].distToPerson = c[i + m + 1].distToPerson;
    }

    int i = 0, j = 0;
    int k = l;
    while(i < l_size && j < r_size){
        // If ith point in l_arr is closer to the person than jth point in r_arr,
        // set the spot at k in the original coords array to the ith point in l_arr
        if( compareTo(&l_arr[i], &r_arr[j]) == CLOSER ){
            c[k] = l_arr[i];
            i++;
        }
        else{
            c[k] = r_arr[j];
            j++; 
        }
        k++;
    }

    // Insert the points of whichever subarray hasn't been used up yet 
    // into the original coords array
    while(i < l_size){
        c[k] = l_arr[i];
        i++;
        k++;
    }
    while(j < r_size){
        c[k] = r_arr[j];
        j++;
        k++;
    }
    free(l_arr);
    free(r_arr);
}
/* Sorts the coordinates with respect to each's distance to the person in ascending order.
   If the length of the subarray reaches the threshold t, use insertion sort on the subarray
*/
void merge_sort(coords* coords, int l, int r, int t){
    if( (r + 1 - l) <= t ){
        insertion_sort(coords, l, r);
        return;
    }
    if(r > l){
        int mid = (r+l) / 2;
        merge_sort(coords, l, mid, t);
        merge_sort(coords, mid+1, r, t);
        merge(coords, l, mid, r);
    }
}

/* Wrapper function for sorting the garages by coordinate */
void sort(coords* gCoords, int n, int threshold){
    merge_sort(gCoords, 0, n-1, threshold);
}

/* Prints coords to console in the format: xi, yi*/
void print_coords(coords* c, int n){
    for(int i = 0; i < n; i++){
        printf("%d %d\n", c[i].x, c[i].y);
    }
}

/* Checks if the numQueries amount of points from the input are in the garage coordinates array
   If not found, print out the points that weren't found
   If found, print out the points and where they were found
 */
void handle_queries(coords* c, int numGarages, int numQueries){
    for(int i = 0; i < numQueries; i++){
        int x, y;
        scanf("%d %d", &x, &y);

        coords temp;
        temp.x = x;
        temp.y = y;
        temp.distToPerson = calcDist(x, y);

        int index = bin_search(c, numGarages, &temp);
        if(index == -1){
            printf("%d %d no garage found\n", x, y);
        }
        else{
            printf("%d %d garage found at position %d in the order\n", x, y, index+1);
        }
    }
}

int main(){
    int numGarages, numPoints, threshold;
    coords* c = ReadData(&numGarages, &numPoints, &threshold);
    sort(c, numGarages, threshold);

    print_coords(c, numGarages);

    handle_queries(c, numGarages, numPoints);

    free(c);
    
    return 0;
}