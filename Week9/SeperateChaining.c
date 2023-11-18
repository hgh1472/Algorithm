#include <stdio.h>
#include <stdlib.h>

typedef struct hashTable {
    int key;
    struct hashTable *next;
} hashTable;

int useHashFunction(int x, int M) { return (x % M); }

hashTable insertKeyToTable(hashTable hashTable_v, int key) {
    if (hashTable_v.key == 0) {
        hashTable_v.key = key;
        return hashTable_v;
    }
    hashTable *temp = hashTable_v.next;
    hashTable *new = (hashTable *)malloc(sizeof(hashTable));
    new->key = hashTable_v.key;
    new->next = hashTable_v.next;
    hashTable_v.key = key;
    hashTable_v.next = new;
    printf("next : %d\n", hashTable_v.next->key);
    return hashTable_v;
}

hashTable *insertKey(hashTable *hashTable, int key, int M) {
    int v = useHashFunction(key, M);
    hashTable[v] = insertKeyToTable(hashTable[v], key);
    return hashTable;
}

int findKey(hashTable hashTable_v, int key) {
    int count = 1;
    hashTable *temp;

    if (hashTable_v.key == key) {
        return 1;
    }
    temp = &hashTable_v;
    while (temp->next != NULL) {
        temp = temp->next;
        count++;
        if (temp->key == key) return count;
    }
    return 0;
}

int findELement(hashTable *hashTable, int key, int M) {
    int v = useHashFunction(key, M);
    return findKey(hashTable[v], key);
}

int deleteKey(hashTable *table, int key, int M) {
    int v = findELement(table, key, M);
    if (v == 0) return 0;
    int index = useHashFunction(key, M);
    if (v == 1) table[index].key = 0;
    hashTable *temp = &table[index];
    for (int i = 1; i < v; i++) {
        temp = temp->next;
    }
}

void printHashTable(hashTable *hashtable, int M) {
    hashTable *tmp;

    for (int i = 0; i < M; i++) {
        if (hashtable[i].key != 0) {
            printf(" %d", hashtable[i].key);
        }
        if (hashtable[i].next != NULL) {
            tmp = hashtable[i].next;
            while (tmp != NULL) {
                printf(" %d", tmp->key);
                tmp = tmp->next;
            }
        }
    }
    printf("\n");
}

int main() {
    int M, key;
    char command;
    hashTable *bucket;

    scanf("%d", &M);
    bucket = (hashTable *)malloc(sizeof(hashTable) * M);
    for (int i = 0; i < M; i++) {
        bucket[i].key = 0;
        bucket[i].next = NULL;
    }
    getchar();
    while (1) {
        scanf("%c", &command);
        if (command == 'e') break;
        switch (command) {
            case 'i':
                scanf("%d", &key);
                bucket = insertKey(bucket, key, M);
                break;
            case 's':
                scanf("%d", &key);
                printf("%d\n", findELement(bucket, key, M));
                break;
            case 'd':
                break;
            case 'p':
                printHashTable(bucket, M);
                break;
            default:
                break;
        }
        getchar();
    }
    return 0;
}