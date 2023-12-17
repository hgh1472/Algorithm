#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    int A[10] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    int s[11];

    s[0] = 0;
    int maxSum = -2147483647, maxi = 0, k = 0;
    int maxj;
    int i = 1;
    while (i < 11) {
        s[i] = max(s[i - 1] + A[i], A[i]);
        if (s[i - 1] < 0)
            k = i;
        if (maxSum < s[i]) {
            maxSum = s[i];
            maxi = k;
            maxj = i;
        }
        i++;
    }
    printf("%d %d\n", maxi, maxj);
    return 0;
}