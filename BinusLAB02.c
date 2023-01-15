#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data { char name[30], type[30]; int price, stock; } datas[150];
int menu = 0, count = 0, total = 0;

void importData()
{
    FILE *fp = fopen("testdata.in", "r");
    char temp = fgetc(fp);
    if (temp == EOF) return;
    else ungetc(temp, fp);
    while (!feof(fp))
    {
        int multiple = 1;
        fscanf(fp, "%[^#]#%[^#]#%d#%d\n", datas[count].name, datas[count].type, &datas[count].price, &datas[count].stock);
        if (!strcmp("Small", datas[count].type)) multiple = 1;
        else if (!strcmp("Medium", datas[count].type)) multiple = 2;
        else multiple = 4;
        total += (multiple * datas[count].stock);
        count++;
    }
    fclose(fp);
}

void exportData()
{
    FILE *fp = fopen("testdata.in", "r");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s#%s#%d#%d\n", datas[i].name, datas[i].type, datas[i].price, datas[i].stock);
    }
    fclose(fp);
}

int searchItem(char search[])
{
    for (int i = 0; i < count; i++)
    {
        if (!strcmp(datas[i].name, search)) return i;
    }
    return -1;
}

void sortItem(int low, int high)
{
    if (low < high)
    {
        char pivot[30]; strcpy(pivot, datas[high].name); int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (strcmpi(datas[j].name, pivot) < 0)
            {
                i++; struct data temp = datas[i]; datas[i] = datas[j]; datas[j] = temp;
            }
        }
        struct data temp = datas[i + 1]; datas[i + 1] = datas[high]; datas[high] = temp;
        int partition = i + 1;
        sortItem(low, partition - 1); sortItem(partition + 1, high);
    }
}

void displayMenu()
{
    system("cls");
    printf("Electronics 2.0!\n");
    printf("================\n");
    printf("1. Insert Electronic Stock\n");
    printf("2. View Electronic List   \n");
    printf("3. Sell Electronic        \n");
    printf("4. Exit                   \n");
    printf(">> "); scanf("%d", &menu); getchar();
}

void displayItem()
{
    system("cls");
    printf("================================================================================\n");
    printf("| %-25s | %-25s | %-11s | %-6s |\n", "Electronic Name", "Electronic Type", "Price", "Stock");
    printf("================================================================================\n");
    for (int i = 0; i < count; i++)
    {
        printf("| %-25s | %-25s | Rp.%-8d | %-6d |\n", datas[i].name, datas[i].type, datas[i].price, datas[i].stock);
    }
    printf("================================================================================\n");
}

void menu1()
{
    system("cls");
    int choice = -1, tempPrice = -1, tempStock = -1, multiple = -1, limit = -1;
    char tempName[30] = {}, tempType[30] = {};
    while (choice < 0 || choice > 2)
    {
        printf("Select this two option    \n");
        printf("1. Insert new item        \n");
        printf("2. Add existing item stock\n");
        printf("0. Back                   \n");
        printf(">> "); scanf("%d", &choice); getchar();
    }
    switch (choice)
    {
        case 0: return;
        case 1:
            {
                if (total == 150)
                {
                    printf("There is no spaces left\n");
                    return;
                }
                else
                {
                    tempStock = -1;
                    while (strlen(tempName) <= 0 || searchItem(tempName) != -1)
                    {
                        printf("Input Item Name [5 - 25 Characters | Unique]: ");
                        gets(tempName);
                    }
                    while (strcmp("Small", tempType) && strcmp("Medium", tempType) && strcmp("Big", tempType))
                    {
                        printf("Input Item Type [Small | Medium | Big]: ");
                        gets(tempType);
                    }
                    if (!strcmp("Small", tempType)) { multiple = 1; limit = 200000; }
                    else if (!strcmp("Medium", tempType)) { multiple = 2; limit = 1500000; }
                    else { multiple = 4; limit = 10000000; }
                    while (tempPrice < 0 || tempPrice > limit)
                    {
                        printf("Input Item Price [Max %d]: ", limit);
                        scanf("%d", &tempPrice); getchar();
                    }
                    while (tempStock < 0 || (multiple * tempStock) + total > 150)
                    {
                        if ((multiple * tempStock) + total > 150) printf("Input stock is more than available capacity [%d spaces]!\n", 150 - total);
                        printf("Input Item Stock [more than 0]: ");
                        scanf("%d", &tempStock); getchar();
                    }
                    strcpy(datas[count].name, tempName); strcpy(datas[count].type, tempType);
                    datas[count].price = tempPrice;
                    datas[count].stock += tempStock;
                    total += (multiple * datas[count].stock);
                    sortItem(0, count); count++;
                    printf("Successfully inserted new item!\n");
                    printf("Press enter to continue..."); getchar();
                }
            }
            break;
        case 2:
            {
                int index = -1; tempStock = -1;
                char search[30] = {};
                displayItem();
                while (strlen(search) <= 0 || index == -1)
                {
                    if (!strcmp("back", search)) return;
                    if (index == -1) printf("Please input existing Electronic Name!\n");
                    printf("Input Electronic Name you want to add stock [Input \"back\" to back]: ");
                    gets(search); index = searchItem(search);
                }
                if (!strcmp("Small", datas[index].type)) multiple = 1;
                else if (!strcmp("Medium", datas[index].type)) multiple = 2;
                else multiple = 4;
                while (tempStock < 0 || (multiple * tempStock) + total > 150)
                {
                    if ((multiple * tempStock) + total > 150) printf("Input stock is more than available capacity [%d spaces]!\n", total);
                    printf("Input how many stock you want to add: ");
                    scanf("%d", &tempStock); getchar();
                }
                datas[index].stock += tempStock;
                total += (multiple * tempStock);
                printf("Successfully add stock!\n");
                printf("Press enter to continue..."); getchar();
            }
            break;
    }
}

void menu2()
{
    displayItem();
    printf("| %-67s | %5.1lf%% |\n", "Used Capacity Percentage", (double)total / 150 * 100);
    printf("================================================================================\n");
    printf("Press enter to continue..."); getchar();
}

void menu3()
{
    int index = -1, tempStock = -1, multiple = -1;
    char search[30] = {};
    displayItem();
    while (strlen(search) <= 0 || index == -1)
    {
        if (!strcmp("back", search)) return;
        if (index == -1) printf("Please input existing Electronic Name!\n");
        printf("Input Electronic Name you want to sell [Input \"back\" to back]: ");
        gets(search); index = searchItem(search);
    }
    while (tempStock < 1 || tempStock > datas[index].stock)
    {
        printf("Input item quantity you want to sell [1-%d]: ", datas[index].stock);
        scanf("%d", &tempStock); getchar();
    }
    datas[index].stock -= tempStock;
    printf("\n\n");
    printf("Successfully sold item!\n");
    printf("=======================\n");
    printf("Transaction Details    \n");
    printf("=======================\n");
    printf("Electronic Name: %s\n", datas[index].name);
    printf("Electronic Type: %s\n", datas[index].type);
    printf("Quantity: %d       \n", tempStock);
    printf("Total Price: %d    \n", tempStock * datas[index].price);
    printf("Press enter to continue..."); getchar();
    if (!strcmp("Small", datas[index].type)) multiple = 1;
    else if (!strcmp("Medium", datas[index].type)) multiple = 2;
    else multiple = 4;
    total -= (multiple * tempStock);
    if (datas[index].stock <= 0)
    {
        for (int i = index; i < count; i++) datas[i] = datas[i + 1];
        count--;
    }
}

int main()
{
    importData();
    while (menu != 4)
    {
        displayMenu();
        switch (menu)
        {
            case 1: menu1(); break;
            case 2: menu2(); break;
            case 3: menu3(); break;
            default: break;
        }
    }
    exportData();
    return 0;
}