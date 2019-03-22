#include "typedef.h"
#include <stdlib.h>
#include <stdio.h>


int main()
{
    const int N = 4, M = 5;
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        matrix[i] = (int*) malloc(M * sizeof(int));


    randomMatrix(matrix, N, M);
    printMatrix(matrix, N, M);
    int column = 0;
    int lastPosition = lastMaxInColumnPosition(matrix, N, M, column);
    printf("max position in column %d: [%d][%d]\n", column, lastPosition, column);
    printf("max value in column %d: %d\n", column, matrix[lastPosition][column]);

    sortedMatrix(matrix, N, M);
    printMatrix(matrix, N, M);
    lastPosition = lastMaxInColumnPosition(matrix, N, M, column);
    printf("max position in column %d: [%d][%d]\n", column, lastPosition, column);
    printf("max value in column %d: %d\n", column, matrix[lastPosition][column]);

    inputMatrix(matrix, N, M);
    printMatrix(matrix, N, M);
    lastPosition = lastMaxInColumnPosition(matrix, N, M, column);
    printf("max position in column %d: [%d][%d]\n", column, lastPosition, column);
    printf("max value in column %d: %d\n", column, matrix[lastPosition][column]);


    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}
