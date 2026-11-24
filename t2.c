#include <stdio.h>

int main(void) {
    FILE *fp;

    fp = fopen("attendance.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    int rolls[5] = {1, 2, 3, 4, 5};
    char names[5][16] = {"Ayesha", "Bilal", "Hamza", "Sana", "Zainab"};
    int attended[5] = {18, 14, 20, 12, 16};

    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%-3d %-15s %3d\n", rolls[i], names[i], attended[i]);
    }
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) {
        return 1;
    }

    int r, leave, roll, lectures;
    char name[16];

    printf("Roll number: ");
    scanf("%d", &r);

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %15s %d", &roll, name, &lectures);

    float pct = (lectures / 20.0f) * 100.0f;
    printf("%s: %d / 20 (%.1f%%)", name, lectures, pct);
    if (pct < 75.0f) {
        printf(" Short attendance");
    }
    printf("\n");

    printf("Roll number for leave: ");
    scanf("%d", &r);
    printf("Lectures: ");
    scanf("%d", &leave);

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fscanf(fp, "%d %15s %d", &roll, name, &lectures);

    lectures += leave;
    pct = (lectures / 20.0f) * 100.0f;
    printf("%s: now %d / 20 (%.1f%%)\n", name, lectures, pct);

    fseek(fp, (r - 1) * 24, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", roll, name, lectures);
    fflush(fp);

    fseek(fp, -24, SEEK_END);
    fscanf(fp, "%d %15s %d", &roll, name, &lectures);
    printf("Last record: %d %s %d\n", roll, name, lectures);

    fclose(fp);
    return 0;
}