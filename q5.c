#include <stdio.h>

int areLayersEqual(int A[3][3][3], int l1, int l2) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(A[l1][i][j] != A[l2][i][j]) return 0;
    return 1;
}

void printLayer(int A[3][3][3], int l) {
    printf("Layer %d:\n", l);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) printf("%5d ", A[l][i][j]);
        printf("\n");
    }
}

int main() {
    int A[3][3][3];
    printf("Enter 27 integers for 3x3x3 array, layer by layer:\n");
    for(int l=0;l<3;l++){
        printf("Layer %d:\n", l);
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d", &A[l][i][j]);
    }

    // print layers
    for(int l=0;l<3;l++){
        printLayer(A, l);
        printf("\n");
    }

    // pairwise comparisons
    for(int i=0;i<3;i++){
        for(int j=i+1;j<3;j++){
            int eq = areLayersEqual(A, i, j);
            printf("Layer %d == Layer %d : %s\n", i, j, eq ? "YES" : "NO");
        }
    }

    // summary: list identical groups
    int checked[3] = {0,0,0};
    for(int i=0;i<3;i++){
        if(checked[i]) continue;
        int group[3]; int gcount=0;
        group[gcount++]=i;
        for(int j=i+1;j<3;j++){
            if(areLayersEqual(A,i,j)){
                group[gcount++]=j;
                checked[j]=1;
            }
        }
        if(gcount>1) {
            printf("Layers equal group: ");
            for(int k=0;k<gcount;k++){
                printf("%d ", group[k]);
            }
            printf("\n");
        } else {
            printf("Layer %d is unique (no identical layer found).\n", i);
        }
    }

    return 0;
}
