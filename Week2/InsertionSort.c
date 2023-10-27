#include <stdio.h>
#include <stdlib.h>

/*
첫 번째 반복문에서 0번째를 제외하고 배열을 훑는다.
두 번째 반복문에서 arr[j]가 arr[pass]보다 크면 바꾸고 반복문을 진행한다.
즉, arr[pass]가 자신의 앞에를 훑으면서 자리를 찾아가는 것임 -> 앞의 배열이 정렬된 상태이기 때문에 가능하다.
*/
void insertion_sort(int n, int *arr)
{
    int pass, j, tmp, save;

    for (pass = 1; pass < n; pass++)
    {
        save = arr[pass]; // 보고있는 값.
        j = pass - 1;
        while (j >= 0 && arr[j] > save)
        {
            arr[j + 1] = arr[j];
            j--;
            arr[j + 1] = save;
        }
    }
}

int main()
{
    int n, i, *arr;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    insertion_sort(n, arr);
    for (i = 0; i < n; i++)
        printf(" %d", arr[i]);
    printf("\n");
    return 0;
}