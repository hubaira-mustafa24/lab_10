#include <stdio.h>

#define RECORD_SIZE 42

int main(void) {
    FILE *fp;

    
    fp = fopen("items.txt", "w");
    if (fp == NULL) {
        printf("Error opening items.txt for writing.\n");
        return 1;
    }

    int initIds[5]     = {1, 2, 3, 4, 5};
    char initNames[5][21] = {"Rice", "Sugar", "Milk", "CookingOil", "Tea"};
    float initPrices[5] = {250.00f, 160.00f, 220.00f, 560.00f, 450.00f};
    int initStock[5]   = {40, 25, 30, 12, 18};

    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%-4d %-20s %9.2f %5d\n",
                initIds[i], initNames[i], initPrices[i], initStock[i]);
    }
    fclose(fp);

    
    fp = fopen("items.txt", "rb+");
    if (fp == NULL) {
        printf("Error opening items.txt in rb+ mode.\n");
        return 1;
    }

    int itemNo, qty;
    float totalBill = 0.0f;

    while (1) {
        printf("Item no: ");
        if (scanf("%d", &itemNo) != 1 || itemNo == 0) {
            break;
        }

        if (itemNo < 1 || itemNo > 5) {
            printf("Invalid item number.\n");
            continue;
        }

        printf("Quantity: ");
        if (scanf("%d", &qty) != 1 || qty < 0) {
            printf("Invalid quantity.\n");
            continue;
        }

        
        long offset = (long)(itemNo - 1) * RECORD_SIZE;
        fseek(fp, offset, SEEK_SET);

        int id, stock;
        char name[21];
        float price;

        fscanf(fp, "%d %20s %f %d", &id, name, &price, &stock);

        
        if (qty <= stock) {
            float lineTotal = qty * price;
            totalBill += lineTotal;
            stock -= qty;

            printf("%s %d x %.2f = %.2f\n", name, qty, price, lineTotal);

            fseek(fp, offset, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", id, name, price, stock);
            fflush(fp);
        } else {
            printf("Only %d %s in stock\n", stock, name);
        }
    }


    printf("Total bill: %.2f\n", totalBill);
    fclose(fp);

    return 0;
}