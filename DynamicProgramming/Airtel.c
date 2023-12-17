#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    if (a > b)
        return b;
    return a;
}

int main() {
    int A[6] = {0, 1, 3, 6, 11, 17};
    int H[6] = {0, 2, 5, 1, 5, 0};
    int cost;
    int m[6];
    m[0] = 0;
    for (int i = 1; i < 6; i++) {
        m[i] = 1000000;
        for (int k = 0; k < i; k++) {
            cost = m[k] + H[k] + A[i - k];
            m[i] = min(m[i], cost);
        }
    }
    printf("%d\n", m[5]);
    return 0;
}