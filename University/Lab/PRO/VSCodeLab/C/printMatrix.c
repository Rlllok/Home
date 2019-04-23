#include "typedef.h"
#include <stdio.h>

void printMatrix(int** matrix, const int N, const int M)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%4d ", matrix[i][j]);
        printf("\n");
    }
}
