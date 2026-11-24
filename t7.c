#include <stdio.h>

int finalBalance(int trans[], int n, int balance) {
    if (n == 0) {
        return balance;
    }
    return finalBalance(trans + 1, n - 1, balance + trans[0]);
}

int totalDeposits(int trans[], int n) {
    if (n == 0) {
        return 0;
    }
    int add = (trans[0] > 0) ? trans[0] : 0;
    return add + totalDeposits(trans + 1, n - 1);
}

int copyLarge(int trans[], int i, int n, int large[], int k) {
    if (i == n) {
        return k;
    }
    if (trans[i] <= -10000) {
        large[k] = trans[i];
        return copyLarge(trans, i + 1, n, large, k + 1);
    }
    return copyLarge(trans, i + 1, n, large, k);
}

int main(void) {
    int startBalance = 20000;
    int trans[7] = {20000, -5000, -12000, 8000, -25000, -2500, 15000};
    int large[7];

    int bal = finalBalance(trans, 7, startBalance);
    int dep = totalDeposits(trans, 7);
    int largeCount = copyLarge(trans, 0, 7, large, 0);

    printf("Final balance: %d\n", bal);
    printf("Total deposits: %d\n", dep);
    printf("Large withdrawals (%d):", largeCount);
    for (int i = 0; i < largeCount; i++) {
        printf(" %d", large[i]);
    }
    printf("\n");

    return 0;
}