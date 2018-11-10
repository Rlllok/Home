#include <stdio.h>

int A[11];

int main()
{
    int l = 2, k = 0;
    char j;

    for (j = 0; j < 11; j++)
    {
        k = j;
        l += 8;
        k++;

        switch (j)
        {
            case 1:
                k = 0;
                break;
            case 3:
                k += 1;
                break;
            case 5:
                k -= 1;
                break;
            case 6:
                k = 2*l - k;
                break;
            default: k--;
        }

        A[j] = k;
    }

    for ( j = 0; j < 11; j++)
        printf("%d ", A[j]);
    printf("\n");

    return 0;
}
