/*
찾지 못했을 때 case 정리 (마지막 2개만 남았을 때)

key = 20;
1) left = 30, right = 40
    rFE(left - 1, left)가 된다. -> next rFE에서 l > r 이 됨 -> next rFE의 left - 1이 key보다 클 수 있지 않을까? -> prev rFE에서 mid값보다 크기 때문에 온 것.
2) left = 10, right = 15
    rFE(left + 1, right)가 된다. -> next rFE에서 l == r이고 mid값은 key보다 작기 때문에 next next rFE에서 rFE기준 rFE(right + 1, right) 이 된다. left - 1 = right
3) left = 10, right = 40
    rFE(left + 1, right)가 된다. -> next rFE에서 l == r이고 mid 값은 key 보다 크기 떄문에 next next rFE에서 rFE기준 rFE(right, left)가 된다. left - 1 = left;
*/
#include <stdio.h>
#include <stdlib.h>

void FE(int *arr, int n, int key) {
    int l = 0, r = n, mid;

    while (l <= r) {
        mid = (l + r) / 2;
        if (arr[mid] == key) {
            printf(" %d\n", mid);
            return;
        } else if (arr[mid] > key)
            r = mid - 1;
        else
            l = mid + 1;
    }
    printf(" %d\n", l);
}

int main() {
    int n, *arr, k;

    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    FE(arr, n - 1, k);
    return 0;
}