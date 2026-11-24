#include <stdio.h>

int main(void) {
    FILE *fp;

    fp = fopen("temperature.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    char city[11];
    float temp;

    for (int i = 0; i < 5; i++) {
        scanf("%10s %f", city, &temp);
        fprintf(fp, "%-10s %5.1f\n", city, temp);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) {
        return 1;
    }

    int cityNo;
    printf("City number: ");
    scanf("%d", &cityNo);

    fseek(fp, (cityNo - 1) * 17, SEEK_SET);
    fscanf(fp, "%10s %f", city, &temp);
    printf("%s %.1f\n", city, temp);

    float newTemp;
    printf("City number to correct: ");
    scanf("%d", &cityNo);
    printf("New temperature: ");
    scanf("%f", &newTemp);

    fseek(fp, (cityNo - 1) * 17, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", city, newTemp);
    fflush(fp);
    printf("%s updated to %.1f\n", city, newTemp);

    rewind(fp);
    char hottestCity[11];
    float maxTemp = -1e9f;
    int first = 1;

    while (fscanf(fp, "%10s %f", city, &temp) == 2) {
        if (first || temp > maxTemp) {
            maxTemp = temp;
            int j = 0;
            while (city[j] != '\0' && j < 10) {
                hottestCity[j] = city[j];
                j++;
            }
            hottestCity[j] = '\0';
            first = 0;
        }
    }

    if (!first) {
        printf("Hottest city: %s (%.1f)\n", hottestCity, maxTemp);
    }

    fclose(fp);
    return 0;
}