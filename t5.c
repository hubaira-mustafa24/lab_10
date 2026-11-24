#include <stdio.h>

#define RECORD_SIZE 23

int main(void) {
    FILE *fp = fopen("expenses.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    char initCat[4][13] = {"Food", "Transport", "Books", "Mobile"};
    float initAmt[4] = {1200.00f, 500.00f, 850.00f, 300.00f};

    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%-12s %9.2f\n", initCat[i], initAmt[i]);
    }
    fclose(fp);

    char newCat[13];
    float newAmt;
    printf("Category: ");
    scanf("%12s", newCat);
    printf("Amount: ");
    scanf("%f", &newAmt);

    fp = fopen("expenses.txt", "ab");
    if (fp == NULL) {
        return 1;
    }
    fprintf(fp, "%-12s %9.2f\n", newCat, newAmt);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) {
        return 1;
    }

    char cat1[13], cat2[13];
    float amt1, amt2;

    fseek(fp, -2L * RECORD_SIZE, SEEK_END);
    fscanf(fp, "%12s %f", cat1, &amt1);
    fscanf(fp, "%12s %f", cat2, &amt2);
    printf("Latest two: %s %.2f, %s %.2f\n", cat1, amt1, cat2, amt2);

    int entryNo;
    float correctAmt;
    printf("Entry to fix: ");
    scanf("%d", &entryNo);
    printf("Correct amount: ");
    scanf("%f", &correctAmt);

    long offset = (long)(entryNo - 1) * RECORD_SIZE;
    fseek(fp, offset, SEEK_SET);
    fscanf(fp, "%12s %f", cat1, &amt1);

    fseek(fp, offset, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", cat1, correctAmt);
    fflush(fp);

    rewind(fp);
    float total = 0.0f;
    while (fscanf(fp, "%12s %f", cat1, &amt1) == 2) {
        printf("%-12s %9.2f\n", cat1, amt1);
        total += amt1;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}