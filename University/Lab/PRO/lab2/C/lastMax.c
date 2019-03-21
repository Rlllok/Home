#include "typedef.h"

int lastMaxInColumnPosition(int** matrix, int N, int M, int column)
{
    int max = matrix[0][column];
    int position;

    for (int i = 0; i < N; i++){
        if (max <= matrix[i][column]) {
            max = matrix[i][column];
            position = i;
        }

    }

    return position;
}
