#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define INACTIVE -1
#define ERROR -1

int *initBuckeyArray(int *hashTable, int M) {
    hashTable = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++) hashTable[i] = EMPTY;
    return hashTable;
}

int applyHashFunction(int x, int M) { return x % M; }

int isEmpty(int *hashTable, int position) { return hashTable[position] == EMPTY; }

int getNextBucket(int position, int countCollision, int M) { return (position + countCollision) % M; }

int isInactive(int *hashTable, int position) { return hashTable[position] == INACTIVE; }

// 충돌횟수만큼 C를 출력합니다.
void printCountCollision(int countCollision) {
    for (int i = 0; i < countCollision; i++) printf("C");
}

void printFullHashTableErrorMessage(int countCollision) {
    printCountCollision(countCollision);
    printf("%d\n", ERROR);
}

void printNoneExistentKeyErrorMessage(int countCollsion) {
    printCountCollision(countCollsion);
    printf("%d\n", ERROR);
}

void insertItem(int *hashTable, int key, int M) {
    int position = applyHashFunction(key, M);
    int countCollision = 0;
    int b;

    /*
    countCollision = M 이면, 테이블이 꽉 차있다는 것이다.
    따라서 최대 countCollision < M 인 동안 반복한다.
    이는 모든 셀을 검사하는 것과 같다.
    */
    while (countCollision < M) {
        b = getNextBucket(position, countCollision, M);
        if (isEmpty(hashTable, b) || isInactive(hashTable, b)) {  // 비어있거나 비활성화 상태라면 삽입한다.
            hashTable[b] = key;
            printCountCollision(countCollision);
            printf("%d\n", b);
            return;
        } else  // 셀이 ACTIVE 상태라면 다음 셀로 넘어간다.
            countCollision++;
    }

    // 테이블이 꽉 차있는 경우.
    printFullHashTableErrorMessage(countCollision);
}

void findElement(int *hashTable, int key, int M) {
    int position = applyHashFunction(key, M);
    int countCollision = 0;
    int b;

    /*
    countCollision = M 이면, 테이블이 꽉 차있다는 것이다.
    따라서 최대 countCollision < M 인 동안 반복한다.
    이는 모든 셀을 검사하는 것과 같다.
    */
    while (countCollision < M) {
        b = getNextBucket(position, countCollision, M);
        if (isEmpty(hashTable, b)) {  // 비어 있는 셀을 만나면 탐색 실패
            printCountCollision(countCollision);
            printf("%d\n", ERROR);
            return;
        } else if (key == hashTable[b]) {  // key값을 찾은 경우.
            printCountCollision(countCollision);
            printf("%d\n", b);
            return;
        } else  // 다른 값이 있거나, INACTIVE인 경우
            countCollision++;
    }

    // 전체를 탐색했지만, key값이 존재하지 않는 경우
    printNoneExistentKeyErrorMessage(countCollision);
}

void removeElement(int *hashTable, int key, int M) {
    int position = applyHashFunction(key, M);
    int countCollision = 0;
    int b;

    /*
    countCollision = M 이면, 테이블이 꽉 차있다는 것이다.
    따라서 최대 countCollision < M 인 동안 반복한다.
    이는 모든 셀을 검사하는 것과 같다.
    */
    while (countCollision < M) {
        b = getNextBucket(position, countCollision, M);
        if (isEmpty(hashTable, b)) {  // 비어 있는 셀을 만나면 탐색 실패
            printCountCollision(countCollision);
            printf("%d\n", ERROR);
            return;
        } else if (key == hashTable[b]) {  // 발견한다면, 해당 셀을 INACTIVE로 바꾼다.
            hashTable[b] = INACTIVE;
            printCountCollision(countCollision);
            printf("%d\n", b);
            return;
        } else  // 다른 값으로 차있거나 INACTIVE인 경우
            countCollision++;
    }

    // 전체를 탐색했지만, key값이 존재하지 않는 경우
    printNoneExistentKeyErrorMessage(countCollision);
}

void freeHashTable(int *hashTable) { free(hashTable); }

int main() {
    int M, key, *hashTable;
    char command;

    scanf("%d", &M);
    getchar();
    hashTable = initBuckeyArray(hashTable, M);
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
                removeElement(hashTable, key, M);
                break;
            default:
                break;
        }
        getchar();
    }
    freeHashTable(hashTable);
}