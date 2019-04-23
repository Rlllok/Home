#include "typedef.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void randomMatrix(int** matrix, const int N, const int M)
{
    srand(time(NULL));
     for(int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrix[i][j] = rand() % 10;
}

void sortedMatrix(int** matrix, const int N, const int M)
{
    for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                matrix[i][j] = i + j;
}

void inputMatrix(int** matrix, const int N, const int M)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%i", &matrix[i][j]);
}
