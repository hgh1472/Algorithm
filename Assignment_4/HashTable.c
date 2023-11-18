#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define INACTIVE -1

int applyHashFunction(int x, int M) {
    return x % M;
}

int isFull(int countCollsion, int M) {
    if (countCollsion >= M)
        return 1;
    return 0;
}

// key를 삽입할 때 hashTable[position]이 비어있거나, 해시테이블이 꽉 차있으면 탐색을 그만둡니다.
int shouldCheckNextForInsert(int *hashTable, int position, int M, int countCollsion) {
    if (hashTable[position] <= 0)
        return 0;
    if (isFull(countCollsion, M))
        return 0;
    return 1;
}

int shouldCheckNextForFindOrDelete(int *hashTable, int key, int position, int M, int countCollsion) {
    // hashTable[position]이 비어있거나 해당 key일 경우 탐색을 그만둡니다.
    if (hashTable[position] == EMPTY || hashTable[position] == key)
        return 0;
    // 해시테이블에 키가 모두 차있으면 탐색을 그만둡니다.
    if (isFull(countCollsion, M))
        return 0;
    return 1;
}

// 탐색하는 인덱스는 배열의 인덱스이므로 배열의 범위 초과 시 다시 0으로 돌아갑니다.
int movePosition(int position, int M) {
    position++;
    if (position == M)
        position = 0;
    return position;
}

// 충돌횟수만큼 C를 출력합니다.
void printCountCollision(int countCollision) {
    for (int i = 0; i < countCollision; i++)
        printf("C");
}

void insertItem(int *hashTable, int key, int M) {
    int position = applyHashFunction(key, M);
    int countCollision = 0;
    while (shouldCheckNextForInsert(hashTable, position, M, countCollision)) {
        // position을 다음 위치로 옮기고, 충돌 횟수를 증가시킵니다.
        position = movePosition(position, M);
        countCollision++;
    }
    printCountCollision(countCollision);
    if (countCollision == M)
        printf("-1\n");
    else {
        hashTable[position] = key;
        printf("%d\n", position);
    }
}

void findElement(int *hashTable, int key, int M) {
    int position = applyHashFunction(key, M);
    int countCollsion = 0;
    while (shouldCheckNextForFindOrDelete(hashTable, key, position, M, countCollsion)) {
        // position을 다음 위치로 옮기고, 충돌 횟수를 증가시킵니다.
        position = movePosition(position, M);
        countCollsion++;
    }
    if (hashTable[position] != key) {
        printCountCollision(countCollsion);
        printf("-1\n");
        return;
    }
    printCountCollision(countCollsion);
    printf("%d\n", position);
}


void deleteElement(int *hashTable, int key, int M) {
    int position = applyHashFunction(key ,M);
    int countCollision = 0;
    while (shouldCheckNextForFindOrDelete(hashTable, key, position, M, countCollision)) {
        position = movePosition(position, M);
        countCollision++;
    }
    printCountCollision(countCollision);
    if (hashTable[position] == key) {
        hashTable[position] = INACTIVE;
        printf("%d\n", position);
    }
    else
        printf("-1\n");
}

int main() {
    int M, key, *hashTable;
    char command;

    scanf("%d", &M);
    getchar();
    hashTable = (int *)malloc(sizeof(int) * M);
    while (1) {
        scanf("%c", &command);
        if (command == 'e') return 0;
        scanf("%d", &key);
        switch (command) {
            case 'i':
                insertItem(hashTable, key, M);
                break;
            case 's':
                findElement(hashTable, key, M);
                break;
            case 'd':
                deleteElement(hashTable, key, M);
                break;
            default:
                break;
        }
        getchar();
    }
}

/*
10, 11, 3, 1, 2, 5, 7
7 1 2 10 11 3 5
*/