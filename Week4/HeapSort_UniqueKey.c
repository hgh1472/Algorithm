/*
힙 정렬
1) 전체적으로 힙 형태로 만든다.
2) 루트의 key 값과 힙의 마지막 노드 값을 swap한다.
3) downHeap(1)을 n-1을 한채로 수행한다 -> n에는 최대값이 저장됨.
4) 이 과정을 n번 반복하면 배열이 오름차순으로 정렬된다.
*/
#include <stdio.h>
#include <stdlib.h>

int n;
int H[100];

#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

void inPlaceHeapSort();
void downHeap(int i);
void buildHeap();
void printArray();

void inPlaceHeapSort()
{
    int tmp;
    int i = n;

    buildHeap();
    while (n > 1)
    {
        SWAP(H[1], H[n], tmp);
        n--;
        downHeap(1);
    }
    n = i;
    printArray();
}
void downHeap(int i)
{
    if (2 * i > n)
        return;

    int larger = 2 * i, tmp;
    if (2 * i + 1 <= n)
    {
        if (H[2 * i + 1] > H[larger])
            larger = 2 * i + 1;
    }
    if (H[i] > H[larger])
        return;
    SWAP(H[i], H[larger], tmp);
    downHeap(larger);
}

void buildHeap()
{
    for (int i = n / 2; i >= 1; i--)
        downHeap(i);
}

void printArray()
{
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &H[i]);
    inPlaceHeapSort();
}