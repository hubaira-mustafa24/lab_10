#include <stdio.h>
#include <string.h>

#define RECORD_SIZE 39

int main(void) {
    FILE *fp = fopen("hotel.txt", "w+");
    if (fp == NULL) {
        return 1;
    }

    int room, nights;
    char status, guest[21];
    float rate = 8000.00f;

    for (int i = 0; i < 10; i++) {
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", 101 + i, 'F', "-", 0, rate);
    }
    fflush(fp);

    freopen("hotel.txt", "rb+", fp);
    if (fp == NULL) {
        return 1;
    }

    int checkRoom;
    printf("Check-in room: ");
    scanf("%d", &checkRoom);
    printf("Name: ");
    scanf("%20s", guest);
    printf("Nights: ");
    scanf("%d", &nights);

    long offset = (long)(checkRoom - 101) * RECORD_SIZE;
    fseek(fp, offset, SEEK_SET);
    fscanf(fp, "%d %c %20s %d %f", &room, &status, guest, &nights, &rate);

    char newGuest[21];
    int newNights;
    printf("Check-in room: ");
    scanf("%d", &checkRoom);
    printf("Name: ");
    scanf("%20s", newGuest);
    printf("Nights: ");
    scanf("%d", &newNights);

    offset = (long)(checkRoom - 101) * RECORD_SIZE;
    fseek(fp, offset, SEEK_SET);
    fscanf(fp, "%d %c %20s %d %f", &room, &status, guest, &nights, &rate);

    if (status == 'F') {
        fseek(fp, offset, SEEK_SET);
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', newGuest, newNights, rate);
        fflush(fp);
        printf("Room %d booked\n", room);
    } else {
        printf("Room already booked\n");
    }

    rewind(fp);
    int rooms[10];
    char guests[10][21];
    for (int i = 0; i < 10; i++) {
        fscanf(fp, "%d %c %20s %d %f", &rooms[i], &status, guests[i], &nights, &rate);
    }

    char searchName[21];
    printf("Search name: ");
    scanf("%20s", searchName);

    int found = 0;
    for (int i = 0; i < 10; i++) {
        if (strcmp(guests[i], searchName) == 0) {
            printf("%s is in room %d\n", searchName, rooms[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("%s not found\n", searchName);
    }

    int outRoom;
    printf("Check-out room: ");
    scanf("%d", &outRoom);

    offset = (long)(outRoom - 101) * RECORD_SIZE;
    fseek(fp, offset, SEEK_SET);
    fscanf(fp, "%d %c %20s %d %f", &room, &status, guest, &nights, &rate);

    printf("Bill: %d x %.2f = %.2f\n", nights, rate, nights * rate);

    fseek(fp, offset, SEEK_SET);
    fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, rate);
    fflush(fp);

    fclose(fp);
    return 0;
}