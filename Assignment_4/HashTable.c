#include <stdio.h>
#include <stdlib.h>

int main() {
    int M, key, *hashTable;
    char command;

    scanf("%d", &M);
    hashTable = (int *)malloc(sizeof(int) * M);
    while (1) {
        scanf("%c", &command);
        if (command == 'q') return;
        scanf("&d", key);
        switch (command) {
            case 'i':
                break;
            case 's':
                break;
            case 'd':
                break;
            default:
                break;
        }
        getchar();
    }
}