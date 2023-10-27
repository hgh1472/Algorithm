#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열의 두 데이터를 SWAP하는 데에 편리함을 위함.
#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

int *arr_insertion; // 삽입정렬을 수행하는데 사용되는 배열.
int *arr_selection; // 선택정렬을 수행하는데 사용되는 배열.
int *tmp;           // 병합정렬을 사용하는데 사용되는 temp 배열.

// 정렬된 데이터를 입력하기 위해 병합 정렬을 사용했다.
void merge(int list[], int left, int mid, int right)
{
    int i, j, k, l;
    i = left;
    j = mid + 1;
    k = left;

    while (i <= mid && j <= right)
    {
        if (list[i] <= list[j])
            tmp[k++] = list[i++];
        else
            tmp[k++] = list[j++];
    }
    while (i <= mid)
        tmp[k++] = list[i++];
    while (j <= right)
        tmp[k++] = list[j++];
    for (l = left; l <= right; l++)
    {
        list[l] = tmp[l];
    }
}

void merge_sort(int list[], int left, int right)
{
    int mid;

    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

void insertion_sort(int n) // 삽입 정렬
{
    int i, j, idx, tmp;

    for (i = 1; i < n; i++)
    {
        idx = i;

        /*
        j와 j-1을 비교하므로 j >= 1 까지 수행하고,
        정렬된 배열로 들어갈 인자가 앞으로 가야한다면,
        for 문을 반복해서 수행한다.
        */
        for (j = i; j >= 1 && arr_insertion[j] < arr_insertion[j - 1]; j--)
            SWAP(arr_insertion[j], arr_insertion[j - 1], tmp);
    }
}

void selection_sort(int n) // 선택 정렬
{
    int idx;
    int tmp;
    int i, j;

    for (i = n - 1; i > 0; i--)
    {
        idx = 0;
        for (j = 1; j <= i; j++)
        {
            // 최대값이 있는 인덱스를 idx에 저장한다.
            if (arr_selection[idx] < arr_selection[j])
                idx = j;
        }
        SWAP(arr_selection[idx], arr_selection[i], tmp);
    }
}

// 오름차순으로 정렬된 데이터를 내림차순으로 바꾼다.
void reverse_arr(int arr[], int n)
{
    int i, tmp;

    for (i = 0; i < n / 2; i++)
        SWAP(arr[i], arr[n - 1 - i], tmp);
}

int main()
{
    int n, i;
    double start, end;

    srand(time(NULL));
    scanf("%d", &n);
    arr_insertion = (int *)malloc(sizeof(int) * n);
    // arr_selection = (int *)malloc(sizeof(int) * n);
    //  tmp = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        // 배열에 임의의 수를 입력하고, 두 배열의 데이터를 같게 만든다.
        arr_insertion[i] = i;
        // arr_selection[i] = arr_insertion[i];
    }

    // 정렬 안되어있을 때
    printf("--------------\n");
    printf("정렬이 안 된 데이터\n");
    start = (double)clock() / CLOCKS_PER_SEC;
    selection_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("정렬 안됐을 때 선택정렬 : %.5lfms\n", (end - start) * 1000);
    start = (double)clock() / CLOCKS_PER_SEC;
    insertion_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("정렬 안됐을 때 삽입정렬 : %.5lfms\n", (end - start) * 1000);
    printf("--------------\n");
    printf("\n");

    // 오름차순으로 정렬되어있을 떄
    merge_sort(arr_insertion, 0, n - 1); // 배열을 오름차순으로 만든다.
    merge_sort(arr_selection, 0, n - 1); // 배열을 오름차순으로 만든다.
    printf("--------------\n");
    printf("오름차순으로 정렬된 데이터\n");
    start = (double)clock() / CLOCKS_PER_SEC;
    selection_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("오름차순으로 정렬되어있을 때 선택정렬 : %.5lfms\n", (end - start) * 1000);
    start = (double)clock() / CLOCKS_PER_SEC;
    insertion_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("오름차순으로 정렬되어있을 때 삽입정렬 : %.5lfms\n", (end - start) * 1000);
    printf("--------------\n");
    printf("\n");

    // 내림차순으로 정렬되어있을 때
    reverse_arr(arr_insertion, n); // 오름차순인 배열을 내림차순으로 바꾼다.
    reverse_arr(arr_selection, n); // 오름차순인 배열을 내림차순으로 바꾼다.
    printf("--------------\n");
    printf("내림차순으로 정렬된 데이터\n");
    start = (double)clock() / CLOCKS_PER_SEC;
    selection_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("내림차순으로 정렬되어있을 때 선택정렬 : %.5lfms\n", (end - start) * 1000);
    start = (double)clock() / CLOCKS_PER_SEC;
    selection_sort(n);
    end = (double)clock() / CLOCKS_PER_SEC;
    printf("내림차순으로 정렬되어있을 때 선택정렬 : %.5lfms\n", (end - start) * 1000);
    printf("--------------\n");

    free(arr_insertion);
    free(arr_selection);
    free(tmp);
}