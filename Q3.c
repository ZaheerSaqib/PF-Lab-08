/* Q3_matrix_multiplication.c
   Multiply two matrices (max size 3x3). Validate dimensions, then use 3 nested loops.
*/
#include <stdio.h>

int main() {
    int r1,c1,r2,c2;
    int A[3][3], B[3][3], C[3][3];

    printf("Enter rows and cols for first matrix (max 3 3): ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and cols for second matrix (max 3 3): ");
    scanf("%d %d", &r2, &c2);

    if(r1<1 || r1>3 || c1<1 || c1>3 || r2<1 || r2>3 || c2<1 || c2>3){
        printf("Dimensions must be between 1 and 3.\n");
        return 0;
    }

    if(c1 != r2) {
        printf("Cannot multiply: columns of A (%d) != rows of B (%d)\n", c1, r2);
        return 0;
    }

    printf("Enter elements of first matrix (row-wise):\n");
    for(int i=0;i<r1;i++) for(int j=0;j<c1;j++) scanf("%d", &A[i][j]);

    printf("Enter elements of second matrix (row-wise):\n");
    for(int i=0;i<r2;i++) for(int j=0;j<c2;j++) scanf("%d", &B[i][j]);

    // initialize result
    for(int i=0;i<r1;i++) for(int j=0;j<c2;j++) C[i][j]=0;

    // multiply using three nested loops
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            for(int k=0;k<c1;k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // print A
    printf("\nMatrix A:\n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++) printf("%5d ", A[i][j]);
        printf("\n");
    }
    // print B
    printf("\nMatrix B:\n");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++) printf("%5d ", B[i][j]);
        printf("\n");
    }
    // print result
    printf("\nProduct matrix (A x B):\n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++) printf("%7d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
