#include <stdio.h>
#include <stdlib.h>

int H[100];
int n;

#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

/*
삽입식 힙 구현
이미 어떠한 배열이 존재할 때, 이를 힙 구조로 바꾸는 것.
내부노드들에 대해 downHeap 진행 -> 모든 노드들에 대해서 downHeap을 할 필요는 없다.
시간복잡도 O(nlogn)이 아닌 이유?
*/

void upHeap(int index);
void downHeap(int index);
void printHeap();

void printHeap()
{
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}

void downHeap(int index)
{
    if (index * 2 > n)
        return;

    int larger = index * 2, tmp;
    if (index * 2 + 1 <= n)
    {
        if (H[larger] < H[index * 2 + 1])
            larger = index * 2 + 1;
    }
    if (H[index] > H[larger])
        return;
    SWAP(H[index], H[larger], tmp);
    downHeap(larger);
}

void buildHeap()
{
    for (int i = n / 2; i >= 1; i--)
        downHeap(i);
}

void rBuildHeap(int i)
{
    if (i > n)
        return;
    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}

int main()
{
    char command;
    int key;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &H[i]);
    buildHeap();
    printHeap();
}