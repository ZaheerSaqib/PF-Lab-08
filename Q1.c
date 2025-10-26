#include <stdio.h>

void printMatInt(int m[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) printf("%4d ", m[i][j]);
        printf("\n");
    }
}

void printMatFloat(float m[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++) printf("%8.4f ", m[i][j]);
        printf("\n");
    }
}

int determinant3x3(int a[3][3]) {
    // using rule of Sarrus / expansion
    int det = 0;
    det = a[0][0]*(a[1][1]*a[2][2] - a[1][2]*a[2][1])
        - a[0][1]*(a[1][0]*a[2][2] - a[1][2]*a[2][0])
        + a[0][2]*(a[1][0]*a[2][1] - a[1][1]*a[2][0]);
    return det;
}

void transpose3x3(int src[3][3], int dst[3][3]) {
    for(int i=0;i<3;i++)
      for(int j=0;j<3;j++)
        dst[j][i] = src[i][j];
}

void cofactor3x3(int a[3][3], int cof[3][3]) {
    // compute minors * sign for each element
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int minor[2][2];
            int r = 0;
            for(int ii=0; ii<3; ii++){
                if(ii==i) continue;
                int c = 0;
                for(int jj=0; jj<3; jj++){
                    if(jj==j) continue;
                    minor[r][c] = a[ii][jj];
                    c++;
                }
                r++;
            }
            int detMinor = minor[0][0]*minor[1][1] - minor[0][1]*minor[1][0];
            int sign = ((i+j)%2==0) ? 1 : -1;
            cof[i][j] = sign * detMinor;
        }
    }
}

int main() {
    int a[3][3];
    int t[3][3];
    int cof[3][3];
    int adj[3][3];
    float inv[3][3];

    printf("Enter 9 integers (3x3 matrix) row-wise:\n");
    for(int i=0;i<3;i++)
      for(int j=0;j<3;j++)
        scanf("%d", &a[i][j]);

    printf("\nOriginal matrix:\n");
    printMatInt(a);

    // Transpose
    transpose3x3(a, t);
    printf("\nTranspose:\n");
    printMatInt(t);

    // Determinant
    int det = determinant3x3(a);
    printf("\nDeterminant = %d\n", det);

    // Cofactor
    cofactor3x3(a, cof);
    printf("\nCofactor matrix:\n");
    printMatInt(cof);

    // Adjoint = transpose of cofactor
    transpose3x3(cof, adj);
    printf("\nAdjoint (transpose of cofactor):\n");
    printMatInt(adj);

    // Inverse if det != 0  -> inverse = (1/det) * adjoint
    if(det == 0) {
        printf("\nInverse does not exist (Singular matrix, determinant = 0).\n");
    } else {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                inv[i][j] = (float)adj[i][j] / (float)det;

        printf("\nInverse matrix (printed as float):\n");
        printMatFloat(inv);
    }

    return 0;
}
