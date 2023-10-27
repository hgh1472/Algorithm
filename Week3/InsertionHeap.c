#include <stdio.h>
#include <stdlib.h>

int H[100];
int n = 0;

#define SWAP(x, y, tmp) ((tmp) = (x), (x) = (y), (y) = (tmp))

/*
배열로 구현한 삽입식 힙 구현.
배열의 index는 0은 비워두고 1부터 시작한다.

힙에 key를 삽입하는 경우
1) 힙의 마지막 자리에 key를 넣는다.
2) 해당 자리에서 upHeap(index)을 수행한다. (upHeap(index)은 해당 H[index]와 H[index/2]를 비교하여 H[index]가 크다면(자식 노드가 더 큰 경우)
H[index]와 H[index / 2]를 swap 한다.)
3) swap한 후에도 올라간 값이 또 부모의 값보다 클 수 있으므로 upheap(index / 2)를 수행한다.

힙에 key를 삭제하는 경우
1) 힙의 루트의 key값을 마지막 노드의 key 값으로 바꾼다.
2) 바뀐 루트의 key 값으로 downHeap을 수행한다.
*/

void insertItem(int key);
void upHeap(int index);
void removeMax();
void downHeap(int index);
void printHeap();

void insertItem(int key)
{
    H[++n] = key;
    upHeap(n);
}

void removeMax()
{
    printf("%d\n", H[1]);
    H[1] = H[n--];
    downHeap(1);
}

void printHeap()
{
    for (int i = 1; i <= n; i++)
        printf(" %d", H[i]);
    printf("\n");
}

void upHeap(int index)
{
    if (index < 2 || H[index / 2] > H[index])
        return;

    int tmp;
    SWAP(H[index / 2], H[index], tmp);
    upHeap(index / 2);
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

int main()
{
    char command;
    int key;

    while (1)
    {
        scanf("%c", &command);
        if (command == 'q')
            break;
        switch (command)
        {
        case 'i':
            scanf("%d", &key);
            insertItem(key);
            printf("0\n");
            break;
        case 'd':
            removeMax();
            break;
        case 'p':
            printHeap();
            break;
        default:
            break;
        }
        getchar();
    }
}