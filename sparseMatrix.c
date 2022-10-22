#include <stdio.h>

int main() {
    //Variables for limit for rows and columns
    int mRow, mCol;

    //Reading the limits for rows and columns
    printf("Enter the limit for rows: ");
    scanf("%d", &mRow);
    printf("Enter the limit for columns: ");
    scanf("%d", &mCol);

    //Constructing matrix with the given data
    int matrix[mRow][mCol];

    //Populating the matrix
    printf("\n");
    for(int r = 0; r < mRow; r++)
    for(int c = 0; c < mCol; c++) {
        printf("Enter the value of element[%d][%d]: ", r, c);
        scanf("%d", &matrix[r][c]);
    }

    //Creating the sparse matrix representation
    printf("\n");
    int mE = (mRow*mCol)/2, smr[mE+1][3], nE = 0;
    for(int r = 0; r < mRow; r++)
    for(int c = 0; c < mCol; c++) {
        if (matrix[r][c] != 0) {
            if (++nE > mE) {
                printf("Error: The matrix is not considered as a sparse matrix\n");
                return 1;
            }

            smr[nE][0] = r;
            smr[nE][1] = c;
            smr[nE][2] = matrix[r][c];
        }
    }
    smr[0][0] = mRow;
    smr[0][1] = mCol;
    smr[0][2] = nE;

    printf("\nSparse matrix represntation:\n");
    for(int i = 0; i < nE+1; i++) {
        printf("%d\t%d\t%d\n", smr[i][0], smr[i][1], smr[i][2]);
    }

    int smtr[nE+1][3];
    for (int i = 0; i < nE+1; i++) {
        smtr[i][0] = smr[i][1];
        smtr[i][1] = smr[i][0];
        smtr[i][2] = smr[i][2];
    }

    for (int i = 0; i < nE; i++) for (int j = 1; j < nE-i; j++)
    if (smtr[j] > smtr[j+1]) for (int k = 0; k < 3; k++) {
        int temp  = smtr[j][k];
        smtr[j][k] = smr[j+1][k];
        smtr[j+1][k] = temp;
    }

    printf("\nSparse matrix transpose represntation:\n");
    for(int i = 0; i < nE+1; i++) {
        printf("%d\t%d\t%d\n", smtr[i][0], smtr[i][1], smtr[i][2]);
    }
}