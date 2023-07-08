#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int min(int a, int b, int c) {
    int minVal = a;
    if (b < minVal) {
        minVal = b;
    }
    if (c < minVal) {
        minVal = c;
    }
    return minVal;
}

double distance(int x, int y) {
    return fabs(x - y);
}

double dtw(int* sequence1, int length1, int* sequence2, int length2) {
    double cost[length1][length2];
    double path[length1 + length2];
    int pathLength = 0;

    // initializing cost matrix
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            cost[i][j] = 1e9;
        }
    }

    // initializing first row & column of cost matrix
    cost[0][0] = distance(sequence1[0], sequence2[0]);
    for (int i = 1; i < length1; i++) {
        cost[i][0] = cost[i - 1][0] + distance(sequence1[i], sequence2[0]);
    }
    for (int j = 1; j < length2; j++) {
        cost[0][j] = cost[0][j - 1] + distance(sequence1[0], sequence2[j]);
    }

    // finding the rest of the cost matrix
    for (int i = 1; i < length1; i++) {
        for (int j = 1; j < length2; j++) {
            double d = distance(sequence1[i], sequence2[j]);
            cost[i][j] = d + min(cost[i - 1][j], cost[i][j - 1], cost[i - 1][j - 1]);
        }
    }

    //finding the optimal path
    path[0] = cost[length1-1][length2-1];
    pathLength++;
    double distance = 0;
    int i = length1 - 1;
    int j = length2 - 1;
    do {
                if(i==0)
                {
                    path[pathLength] = cost[i][j-1];
                    j--;

                }
                else if(j==0)
                {
                    path[pathLength] = cost[i-1][j];
                    i--;
                }
                else
                {
                    path[pathLength] = min(cost[i-1][j],cost[i][j-1],cost[i-1][j-1]);
                    if(path[pathLength]==cost[i-1][j])
                        i--;
                    else if(path[pathLength]==cost[i][j-1])
                        j--;
                    else
                    {
                        i--;
                        j--;
                    }
                }
                pathLength++;
    } while(i!=0 && j!=0);
    path[++pathLength] = cost[0][0];
    for(int i = 0; i< pathLength;i++)
    {
        printf("%f ", path[i]);
        distance += path[i];
    }
    printf("\nPathlength - %d\n", pathLength);
    printf("Total distance : %f\n", distance);

    return distance/pathLength;
}

int main() {
    int sequence1[] = {1, 7, 4, 8, 2, 9, 6 ,5 ,2, 0};
    int sequence2[] = {1, 2, 8, 5, 5, 1, 9, 4, 6, 5};
    int length1 = sizeof(sequence1) / sizeof(sequence1[0]);
    int length2 = sizeof(sequence2) / sizeof(sequence2[0]);

    double dtwDistance = dtw(sequence1, length1, sequence2, length2);
    printf("DTW distance: %lf\n", dtwDistance);

    return 0;
}

int* reduceArrayByHalf(int* array, int length) {
    int i, j;

    int* array1;
    for (i = 0, j = 0; i < length; i += 2, j++) {
        array1[j] = array[i];
    }
}

double fastdtw(int* sequence1, int length1, int* sequence2, int length2, int radius) {

    int minTSsize = radius + 2;

    if(length1<=minTSsize || length2<=minTSsize)
    {
        return dtw(sequence1,length1,sequence2,length2);
    }

    else
    {
        int* shrunk1 = reduceArrayByHalf(sequence1, length1);
        int* shrunk2 = reduceArrayByHalf(sequence2, length2);

        //lowResPath = fastdtw(shrunk1,shrunkLength1,shrunk2,shrunkLength2,radius);
        //window = expandedResWindow(lowResPath, sequence1, sequence2, radius);
        //constrainedDTW(sequence1,sequence2,window);


    }


}
