#include <stdio.h>
#include <stdlib.h>

#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

/*
이중 for 문 사용.
배열의 0부터 n-2 번째까지 반복 -> pass
    그 다음 반복문에서 pass 뒤의 숫자들을 확인하면서 최소값을 pass의 자리에 넣는다.
*/
void selection_sort(int n, int *arr)
{
    int pass, minLoc, tmp, j;

    for (pass = 0; pass < n - 1; pass++)
    {
        minLoc = pass;
        for (j = pass + 1; j < n; j++)
        {
            if (arr[j] < arr[minLoc])
                minLoc = j;
        }
        SWAP(arr[pass], arr[minLoc], tmp);
    }
}

int main()
{
    int n, i;
    int *arr;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    selection_sort(n, arr);
    for (i = 0; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
    return 0;
}