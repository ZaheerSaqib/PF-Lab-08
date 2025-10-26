#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// helper: print yes/no style
void printResult(const char *name, int cond) {
    printf("%-25s : %s\n", name, cond ? "YES" : "NO");
}

// get minor for determinant
void getMinor(int n, double src[MAX][MAX], double dst[MAX][MAX], int skip_r, int skip_c) {
    int r=0,c=0;
    for(int i=0;i<n;i++){
        if(i==skip_r) continue;
        c=0;
        for(int j=0;j<n;j++){
            if(j==skip_c) continue;
            dst[r][c] = src[i][j];
            c++;
        }
        r++;
    }
}

// recursive determinant (works for n up to 5)
double det_rec(int n, double mat[MAX][MAX]) {
    if(n==1) return mat[0][0];
    if(n==2) return mat[0][0]*mat[1][1] - mat[0][1]*mat[1][0];
    double determinant = 0;
    double minor[MAX][MAX];
    for(int c=0;c<n;c++){
        getMinor(n, mat, minor, 0, c);
        double sign = (c % 2 == 0) ? 1 : -1;
        determinant += sign * mat[0][c] * det_rec(n-1, minor);
    }
    return determinant;
}

void matMultiply(int r1, int c1, double A[MAX][MAX], int r2, int c2, double B[MAX][MAX], double C[MAX][MAX]) {
    // C = A * B ; assumes c1 == r2
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            C[i][j] = 0;
            for(int k=0;k<c1;k++) C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int isZeroMatrix(int r, int c, double m[MAX][MAX]) {
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) if(m[i][j] != 0.0) return 0;
    return 1;
}

int isIdentity(int n, double m[MAX][MAX]) {
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if( (i==j && m[i][j] != 1.0) || (i!=j && m[i][j] != 0.0) ) return 0;
    return 1;
}

int isDiagonal(int r, int c, double m[MAX][MAX]) {
    if(r != c) return 0;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            if(i!=j && m[i][j] != 0.0) return 0;
    return 1;
}

int isScalar(int n, double m[MAX][MAX]) {
    if(!isDiagonal(n,n,m)) return 0;
    double val = m[0][0];
    for(int i=0;i<n;i++) if(m[i][i] != val) return 0;
    return 1;
}

int isUpperTriangular(int r, int c, double m[MAX][MAX]) {
    if(r != c) return 0;
    for(int i=1;i<r;i++)
        for(int j=0;j<i;j++)
            if(m[i][j] != 0.0) return 0;
    return 1;
}

int isLowerTriangular(int r, int c, double m[MAX][MAX]) {
    if(r != c) return 0;
    for(int i=0;i<r;i++)
        for(int j=i+1;j<c;j++)
            if(m[i][j] != 0.0) return 0;
    return 1;
}

int isSymmetric(int n, double m[MAX][MAX]) {
    if(n <= 0) return 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(m[i][j] != m[j][i]) return 0;
    return 1;
}

int isSkewSymmetric(int n, double m[MAX][MAX]) {
    for(int i=0;i<n;i++){
        if(m[i][i] != 0.0) return 0; // diagonal must be zero
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(m[i][j] != -m[j][i]) return 0;
    return 1;
}

int equalMatrices(int r1,int c1,double a[MAX][MAX], int r2, int c2, double b[MAX][MAX]) {
    if(r1!=r2 || c1!=c2) return 0;
    for(int i=0;i<r1;i++) for(int j=0;j<c1;j++) if(a[i][j] != b[i][j]) return 0;
    return 1;
}

int isIdempotent(int n, double m[MAX][MAX]) {
    double prod[MAX][MAX];
    matMultiply(n,n,m,n,n,m,prod);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(prod[i][j] != m[i][j]) return 0;
    return 1;
}

int isNilpotent(int n, double m[MAX][MAX]) {
    // check successive powers up to n (A^k == 0 for some k<=n)
    double power[MAX][MAX], temp[MAX][MAX];
    // init power = m (A^1)
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) power[i][j] = m[i][j];
    if(isZeroMatrix(n,n,power)) return 1;
    for(int k=2;k<=n;k++){
        matMultiply(n,n,power,n,n,m,temp); // temp = power * m
        // copy temp -> power
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) power[i][j] = temp[i][j];
        if(isZeroMatrix(n,n,power)) return 1;
    }
    return 0;
}

int main() {
    int r, c;
    double M[MAX][MAX];

    printf("Enter rows and cols (max 5 5): ");
    scanf("%d %d", &r, &c);
    if(r<1 || r>5 || c<1 || c>5) {
        printf("Invalid size. Must be between 1 and 5.\n");
        return 0;
    }

    printf("Enter matrix elements row-wise:\n");
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            scanf("%lf", &M[i][j]);

    printf("\nMatrix entered:\n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) printf("%7.2f ", M[i][j]);
        printf("\n");
    }

    int isSquare = (r==c);
    printResult("Square Matrix", isSquare);
    printResult("Rectangular Matrix", !isSquare);
    printResult("Zero / Null Matrix", isZeroMatrix(r,c,M));
    if(isSquare) printResult("Identity Matrix", isIdentity(r,M));
    else printResult("Identity Matrix", 0);
    printResult("Diagonal Matrix", isDiagonal(r,c,M));
    if(isSquare) printResult("Scalar Matrix", isScalar(r,M));
    else printResult("Scalar Matrix", 0);
    printResult("Upper Triangular Matrix", isUpperTriangular(r,c,M));
    printResult("Lower Triangular Matrix", isLowerTriangular(r,c,M));
    if(isSquare) printResult("Symmetric Matrix", isSymmetric(r,M));
    else printResult("Symmetric Matrix", 0);
    if(isSquare) printResult("Skew-Symmetric Matrix", isSkewSymmetric(r,M));
    else printResult("Skew-Symmetric Matrix", 0);

    if(isSquare) {
        double Md[MAX][MAX];
        // copy to double sized for determinant routine
        for(int i=0;i<r;i++) for(int j=0;j<r;j++) Md[i][j] = M[i][j];
        double d = det_rec(r, Md);
        printResult("Singular (det=0)", d == 0.0);
        printResult("Non-Singular (det!=0)", d != 0.0);
    } else {
        printResult("Singular (det=0)", 0);
        printResult("Non-Singular (det!=0)", 0);
    }

    // Row / Column matrix
    printResult("Row Matrix (single row)", r==1 && c>=1);
    printResult("Column Matrix (single column)", c==1 && r>=1);

    // Idempotent and Nilpotent (only meaningful for square)
    if(isSquare) {
        printResult("Idempotent Matrix (A^2 = A)", isIdempotent(r, M));
        printResult("Nilpotent Matrix (A^k = 0 for some k<=n)", isNilpotent(r, M));
    } else {
        printResult("Idempotent Matrix (A^2 = A)", 0);
        printResult("Nilpotent Matrix (A^k = 0 for some k<=n)", 0);
    }

    // Equal Matrix - ask user if they want to compare with second matrix
    printf("\nDo you want to compare with another matrix for equality? (1=Yes / 0=No): ");
    int choice; scanf("%d", &choice);
    if(choice == 1) {
        int r2, c2;
        double N[MAX][MAX];
        printf("Enter rows and cols of second matrix: ");
        scanf("%d %d", &r2, &c2);
        if(r2<1 || r2>5 || c2<1 || c2>5) {
            printf("Invalid size for second matrix.\n");
        } else {
            printf("Enter second matrix elements:\n");
            for(int i=0;i<r2;i++) for(int j=0;j<c2;j++) scanf("%lf", &N[i][j]);
            printResult("Equal Matrix (A == B)", equalMatrices(r,c,M, r2,c2,N));
        }
    }

    return 0;
}
