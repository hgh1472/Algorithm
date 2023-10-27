#include <stdio.h>

int main() {
    int a, b, n;
    char command;

    scanf("%d %d %d", &a, &b, &n);
    getchar();
    for (int i = 0; i < n; i++) {
        scanf("%c", &command);
        if (command == 'Y')
            a = (a + b) / 2 + 1;
        else
            b = (a + b) / 2;
    }
    printf("%d\n", a);
    return 0;
}