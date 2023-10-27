/*
퀵 정렬을 배열로 구현.
다른 점은 정렬할 때 pivot과 같은 값은 가운데에 몰아서 그 부분은 빼고 정렬을 수행한다.
예를 들어 pivot과 같은 값이 들어있다면, 다음 정렬의 범위는 두 개의 index를 제외한 범위이다.

1) findPivot으로 무작위의 피벗값을 정한다.
2) inPlacePartition으로 피벗을 기준으로 작은 값과 큰 값을 나눈다.
3) findAB로 피벗과 같은 값은 가운데로 몰아준다.
4) findAB를 수행하면서 나온 a,b값을 다음 정렬의 index로 넘겨준다.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

int findPivot(int left, int right) {
    srand(time(NULL));
    return (left + rand() % ((right + 1) - left));
}

int inPlacepartition(int *arr, int l, int r, int p) {
    int pivot = arr[p];
    int i = l, j = r - 1, tmp;
    SWAP(arr[p], arr[r], tmp);
    while (i <= j) {
        while (i <= j && arr[i] <= pivot) i++;
        while (i <= j && arr[j] >= pivot) j--;
        if (i < j) SWAP(arr[i], arr[j], tmp);
    }

    // 오른쪽 끝에 두었던 pivot을 올바른 위치에 넣는다. (i의 위치는 pivot보다 큰 값이 나오기 시작한 index -> pivot의 위치(right)와 바꾸면서 pivot은 올바른 위치를 찾는다.)
    SWAP(arr[i], arr[r], tmp);
    return i;
}

void findAB(int *arr, int *a, int *b, int p, int l, int r) {
    int i, equal = 0, tmp;

    for (i = l; i < p - equal; i++) {
        if (arr[i] == arr[p]) {
            equal++;
            SWAP(arr[i], arr[p - equal], tmp);
        }
    }
    *a = p - equal;
    equal = 0;
    for (i = p + 1; i <= r; i++) {
        if (arr[i] == arr[p]) {
            equal++;
            SWAP(arr[i], arr[p + equal], tmp);
        }
    }
    *b = p + equal;
}

void inPlaceQuickSort(int *arr, int l, int r) {
    if (l >= r) return;

    int a, b;
    int p = findPivot(l, r);
    p = inPlacepartition(arr, l, r, p);
    findAB(arr, &a, &b, p, l, r);
    inPlaceQuickSort(arr, l, p - 1);
    inPlaceQuickSort(arr, p + 1, r);
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) printf(" %d", arr[i]);
    printf("\n");
}

int main() {
    int n, *arr;

    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    inPlaceQuickSort(arr, 0, n - 1);
    printArray(arr, n);
    free(arr);
    return 0;
}