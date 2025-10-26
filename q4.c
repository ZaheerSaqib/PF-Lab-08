/* Q4_3d_layer_analysis.c
   3x3x3 array layer-wise totals and overall insights.
*/
#include <stdio.h>
#include <limits.h>

int main() {
    int A[3][3][3];
    printf("Enter 27 integers for a 3x3x3 array, layer by layer (layer 0,1,2). Rows then cols:\n");

    for(int layer=0; layer<3; layer++){
        printf("Layer %d:\n", layer);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                scanf("%d", &A[layer][i][j]);
            }
        }
    }

    int overallSum = 0;
    int overallMin = INT_MAX;
    int overallMax = INT_MIN;

    for(int layer=0; layer<3; layer++){
        int sum = 0;
        int min = INT_MAX;
        int max = INT_MIN;
        printf("\nLayer %d matrix:\n", layer);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                int val = A[layer][i][j];
                printf("%5d ", val);
                sum += val;
                if(val < min) min = val;
                if(val > max) max = val;
            }
            printf("\n");
        }
        overallSum += sum;
        if(min < overallMin) overallMin = min;
        if(max > overallMax) overallMax = max;

        double avg = sum / 9.0;
        printf("Layer %d -> Sum: %d, Min: %d, Max: %d, Avg: %.2f\n", layer, sum, min, max, avg);
    }

    double overallAvg = overallSum / 27.0;
    printf("\nOverall across all layers -> Sum: %d, Min: %d, Max: %d, Avg: %.2f\n",
           overallSum, overallMin, overallMax, overallAvg);

    return 0;
}
