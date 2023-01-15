#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//12 Oktober 2022
void prob1A(), prob1B(), prob1C();

//19 Oktober 2022
void prob2A(), prob2B(), prob2C();

//26 Oktober 2022
void prob3A(), prob3B(), prob3C();

//02 November 2022
void prob4A(), prob4B(), prob4C();

//09 November 2022
void prob5A(), prob5B(), prob5C();

//16 November 2022
void prob6A(), prob6B(), prob6C();

//Global AddOns
int fibocount = 0;

int cmpfunc(const void * a, const void * b) { return ( *(int*)a - *(int*)b ); }

int fibonacci(int number) { fibocount++; return number == 0 ? 0 : number == 1 ? 1 : fibonacci(number - 1) + fibonacci(number - 2); }

int arraysum(int *array, int size) { return size == 0 ? array[0] : array[size] + arraysum(array, size - 1); }

int row = 0, column = 0, paccount = 0;

void floods(char array[row + 1][column + 1], int posX, int posY)
{
    switch (array[posX][posY])
    {
        case '.': { paccount++; array[posX][posY] = ' '; } break;

        case 'S': { array[posX][posY] = ' '; } break;

        case '#': default: return;
    }
    if (posX + 1 <= row) floods(array, posX + 1, posY); //Bottom

    if (posY + 1 <= column) floods(array, posX, posY + 1); //Right

    if (posX - 1 > 0) floods(array, posX - 1, posY); //Top

    if (posY - 1 > 0) floods(array, posX, posY - 1); //Left
}

int main() { prob6A(); return 0; }

void prob1A()
{
    long long int ind1, ind2, index, i;
    
    scanf("%lld %lld %lld", &ind1, &ind2, &index); getchar();

    for (i = 2; i <= index; i++)
    {
        long long int temp = ind2; ind2 += ind1; ind1 = temp;
    }
    printf("%lld\n", index == 0 ? ind1 : ind2);
}

void prob1B()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        long long int result = 0, index, first, second;

        scanf("%lld %lld %lld", &index, &first, &second); getchar();

        for (i = 2; i <= index; i++)
        {
            long long int temp = second; second -= first; first = temp;
        }
        printf("Case #%d: %lld\n", i, index == 0 ? first : second);
    }
}

void prob1C()
{
    int input, i; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        long long int A, B, temp = 0;
        
        scanf("%lld %lld", &A, &B); getchar();

        while (A != temp && A != B)
        {
            temp = A; A = A ? A : !(A % 2) ? A / 2 : (A * 3) + 1;
        }
        printf("Case #%d: %s\n", i, A == B ? "YES" : "NO");
    }
}

void prob2A()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int target; char result[20][20000] = {};

        scanf("%d %s %s", &target, &result[0], &result[1]); getchar();

        for (j = 2; j <= target; j++)
        {
            sprintf(result[j], "%s%s", result[j - 1], result[j - 2]);
        }
        printf("Case #%d: %s\n", i, result[target]);
    }
}

void prob2B()
{
    int input, i, j; scanf ("%d", &input); getchar();

	for (i = 1; i <= input; i++)
	{
		int number; scanf ("%d", &number); getchar();

        fibonacci(number); printf ("Case #%d: %d\n", i, fibocount);
	}
}

void prob2C()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int number; scanf("%d", &number); int values[number], result = 0;

        for (j = 0; j < number; j++) scanf("%d", &values[j]);

        qsort(values, number, sizeof(int), cmpfunc);

        for (j = number - 1; j >= 0; j--) if (values[j] == values[number - 1]) result++;

        printf("Case #%d: %d\n", i, result);
    }
}

void prob3A()
{
    int size, i, j; scanf("%d", &size); int values[size][size];

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++) scanf("%d", &values[i][j]);
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++) printf("%s%d", !j ? "" : " ", values[j][i]);

        printf("\n");
    }
}

void prob3B()
{
    int input, i, j; scanf("%d", &input);

    for (i = 1; i <= input; i++)
    {
        int number; scanf("%d", &number); int values[number];

        for (j = 0; j < number; j++) scanf("%d", &values[j]);

        printf("Case #%d: %lld\n", i, arraysum(values, number - 1));
    }
}

void prob3C()
{
    int number, i, j; scanf("%d", &number);
    
    long long int values[number], count = 0;

    for (i = 0; i < number; i++)
    {
        long long int temp, status = 0; scanf("%lld", &temp);

        for (j = 0; j < i; j++) if (values[j] == temp) status = 1;

        if (!status) { values[i] = temp; count++; }
    }
    printf("%lld\n", count);
}

void prob4A()
{
    int input, i, j, k; scanf("%d", &input);

    long long int cumulative[5050] = {}, value;

    for (i = 1; i <= input; i++)
    {
        scanf("%lld", &value);

        cumulative[i] = cumulative[i - 1] + value;
    }
    int number; scanf("%d", &number);

    for (i = 1; i <= number;i++)
    {
        long long int target, max = -1; scanf("%lld", &target);

        for (j = 0; j < input; j++)
        {
            for (k = input; k >= j + 1; k--)
            {
                if (cumulative[k] - cumulative[j] <= target)
                {
                    max = (k - j) > max ? (k - j) : max;

                    break;
                }
            }
        }
        printf("Case #%d: %d\n", i, max);
    }
}

void prob4B()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        long long int values[5005] = {};
        
        long long int size, temp, max = 0; scanf("%d", &size);

        for (j = 0; j < size; j++) scanf("%lld", &values[j]);

        qsort(values, size, sizeof(long long int), cmpfunc);

        for (j = 1; j < (size / 2); j++)
        {
            temp = values[j] - values[j - 1];

            max = j == 1 ? temp : temp > max ? temp : max;
        }
        for (j = (size / 2) + 1; j < size; j++)
        {
            temp = values[j] - values[j - 1];

            max = temp > max ? temp : max;
        }
        printf("Case #%d: %lld\n", i, max);
    }
}

void prob4C()
{
    int input, i; scanf("%d", &input); getchar();

    int values[input];

    for (i = 0; i < input; i++) scanf("%d", &values[i]);

    qsort(values, input, sizeof(int), cmpfunc);

    int number; scanf("%d", &number);

    for (int i = 0; i < number; i++)
    {
        int target; scanf("%d", &target);

        int index = -1, left = 0, right = input - 1;

        while (left <= right)
        {
            int middle = (left + right) / 2;

            if (values[middle] < target) left = middle + 1;
            
            else
            {
                if (values[middle] == target) index = middle + 1;

                right = middle - 1;
            }
        }
        printf("%d\n", index);
    }
}

void prob5A()
{
    int input, i; scanf("%d", &input); getchar();

    struct data { char code[10], name[105]; int credit; } datas[input];

    for (i = 0; i < input; i++)
    {
        gets(datas[i].code); gets(datas[i].name); scanf("%d", &datas[i].credit); getchar();
    }
    int number; scanf("%d", &number); getchar();

    for (i = 0; i < number; i++)
    {
        int target; scanf("%d", &target); getchar();

        printf("Query #%d:\n", i + 1);

        printf("Code: %s\n", datas[target - 1].code);

        printf("Name: %s\n", datas[target - 1].name);

        printf("Credits: %d\n", datas[target - 1].credit);
    }
}

void prob5B()
{
    int input, i, j, k; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        paccount = 0; int posX = 0, posY = 0;
        
        scanf("%d %d", &row, &column); getchar();

        char values[row + 1][column + 1];

        for (j = 1; j <= row; j++)
        {
            for (k = 1; k <= column; k++)
            {
                scanf("%c", &values[j][k]);

                if (values[j][k] == 'S') { posX = j; posY = k; }
            }
            getchar();
        }
        floods(values, posX, posY);
        
        printf("Case #%d: %d\n", i, paccount);
    }
}

void prob5C()
{
    FILE *database = fopen("testdata.in", "r");
    
    int minimum; fscanf(database, "%d\n", &minimum);
    
    char word[1000]; int index = 1, count = 0, status = 1;

    while (fscanf(database, "%s", word) == 1)
    {
        if (word[0] == '#')
        {
            if (count < minimum)
            {
                status = 0;
                
                printf("page %d: %d word(s)\n", index, count);
            }
            count = 0; index++;
        }
        else count++;
    }
    if (status == 1) printf("The essay is correct\n");
        
    fclose(database);
}

void prob6A()
{
    int input, i, j; scanf("%d", &input); getchar();

    long long int *values = (long long int*)malloc(400005 * sizeof(long long int));

    for (i = 1; i <= input; i++) scanf("%lld", &values[i]);

    long long int limit; scanf("%lld", &limit); getchar();

    long long int max = 0, temp = 0;

    for (i = 1; i <= input; i++)
    {
        for (j = i; j >= 1; j--)
        {
            if (i == j) temp = values[j];

            else temp += ((i - j + 1) * values[j]);

            if (temp > limit) break;

            if (temp >= max && temp <= limit) max = temp;
        }
    }
    printf("%lld\n", max);
}

void prob6B()
{
    struct data { char ID[25], name[105], age[5]; } datas[1005];

    int input, i; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        gets(datas[i].ID); gets(datas[i].name); gets(datas[i].age);
    }
    int number; scanf("%d", &number); getchar();

    for (i = 1; i <= number; i++)
    {
        int target; scanf("%d", &target); getchar();

        printf("Query #%d:\n", i);

        printf("ID: %s\n", datas[target].ID);

        printf("Name: %s\n", datas[target].name);

        printf("Age: %s\n", datas[target].age);
    }
}

void prob6C()
{
    int input, i, j, k; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int number, minute, values[10005], count = 0;
        
        scanf("%d %d", &number, &minute); getchar();

        for (j = 0; j < number; j++) scanf("%d", &values[j]);

        for (j = 0; j < number - 1; j++)
        {
            for (k = j + 1; k < number; k++)
            {
                if (values[j] > values[k])
                {
                    int temp = values[j]; values[j] = values[k]; values[k] = temp;

                    count++;
                }
            }
        }
        printf("Case #%d: %lld\n", i, count * minute);
    }
}