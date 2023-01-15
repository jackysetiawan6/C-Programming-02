#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//10 Oktober 2022
void prob1A(), prob1B(), prob1C(), prob1D(), prob1E();

//18 Oktober 2022
void prob2A(), prob2B(), prob2C(), prob2D(), prob2E();

//25 Oktober 2022
void prob3A(), prob3B(), prob3C(), prob3D(), prob3E();

//01 November 2022
void prob4A(), prob4B_1(), prob4B_2(), prob4C(), prob4D(), prob4E();

//09 November 2022
void prob5A(), prob5B(), prob5C(), prob5D();

//AddOns Functions
int compare(const void * a, const void * b) { return ( *(int*)a - *(int*)b ); }

void mergesort(char array[105][105], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergesort(array, left, mid); mergesort(array, mid + 1, right);

        int leftSize = mid - left + 1, rightSize = right - mid;

        char leftArr[leftSize][105], rightArr[rightSize][105];

        for (int i = 0; i < leftSize; i++) strcpy(leftArr[i], array[left + i]);

        for (int i = 0; i < rightSize; i++) strcpy(rightArr[i], array[mid + 1 + i]);

        int i = 0, j = 0, k = left;
        
        while (i < leftSize && j < rightSize)
        {
            if (strcmp(leftArr[i], rightArr[j]) <= 0) { strcpy(array[k], leftArr[i]); i++; }

            else { strcpy(array[k], rightArr[j]); j++; }

            k++;
        }
        while (i < leftSize) { strcpy(array[k], leftArr[i]); i++; k++; }

        while (j < rightSize) { strcpy(array[k], rightArr[j]); j++; k++; }
    }
}
void partition(int* array, int size, int index, int sum)
{
    if (index == size) { printf("%d\n", sum); return; }

    if (2 * index == size) { printf("%d\n", sum + array[2 * index]); return; }

    if (2 * index > size) { printf("%d\n", sum); return; }

    partition(array, size, 2 * index, sum + array[2 * index]);

    partition(array, size, (2 * index) + 1, sum + array[(2 * index) + 1]);
}
int row = 0, column = 0, paccount = 0;

void pacmon(char array[row + 1][column + 1], int posX, int posY)
{
    switch (array[posX][posY])
    {
        case '*': { paccount++; array[posX][posY] = ' '; } break;

        case '.': case 'P': { array[posX][posY] = ' '; } break;

        case '#': default: return;
    }
    if (posX + 1 <= row) pacmon(array, posX + 1, posY); //Bottom

    if (posY + 1 <= column) pacmon(array, posX, posY + 1); //Right

    if (posX - 1 > 0) pacmon(array, posX - 1, posY); //Top

    if (posY - 1 > 0) pacmon(array, posX, posY - 1); //Left
}
int lilieq(int X, int Y)
{
    if (!X || !Y) return 1;

    return (lilieq(X - 1, Y - 1) + lilieq(X - 1, Y) + lilieq(X, Y - 1));
}

int main() { prob5A(); return 0; }

void prob1A()
{
    char name1[101], name2[101]; double height1, height2; int age1, age2;

    scanf("%s %lf %d", name1, &height1, &age1); getchar();

    scanf("%s %lf %d", name2, &height2, &age2); getchar();

    printf("Name 1: %s\nHeight 1: %.2lf\nAge 1: %d\n", name1, height1, age1);

    printf("Name 2: %s\nHeight 2: %.2lf\nAge 2: %d\n", name2, height2, age2);
}

void prob1B()
{
    int input, i; scanf("%d", &input); getchar();

    struct profile
    {
        char name[101], place[101], date[101], school[101], nim[101];

        char age[101], postal[101], sibling[101], height[101], card[101];
    };
    struct profile profiles[105];

    for (i = 1; i <= input; i++)
    {
        gets(profiles[i].name); gets(profiles[i].nim); gets(profiles[i].age);
        
        gets(profiles[i].postal); gets(profiles[i].place); gets(profiles[i].date);
        
        gets(profiles[i].school); gets(profiles[i].sibling); gets(profiles[i].height);
        
        gets(profiles[i].card);
    }
    for (i = 1; i <= input; i++)
    {
        printf("Mahasiswa ke-%d:\n", i);
        
        printf("Nama: %s\n", profiles[i].name);
        
        printf("NIM: %s\n", profiles[i].nim);
        
        printf("Umur: %s\n", profiles[i].age);
        
        printf("Kode Pos: %s\n", profiles[i].postal);
        
        printf("Tempat Lahir: %s\n", profiles[i].place);
        
        printf("Tanggal Lahir: %s\n", profiles[i].date);
        
        printf("Almamater SMA: %s\n", profiles[i].school);
        
        printf("Jumlah Saudara Kandung: %s\n", profiles[i].sibling);
        
        printf("Tinggi Badan: %s\n", profiles[i].height);
        
        printf("NOMOR REKENING: %s\n", profiles[i].card);
    }
}

void prob1C()
{
    int input, i, j; scanf("%d", &input); getchar();

    struct lecturer
    {
        char code[31], name[31], gender[31]; int student;

        struct students { char code[31], name[31], gender[31], father[31], mother[31]; int sibling; } mahasiswa[105];
    };
    struct lecturer dosen[105];
    
    for (i = 1; i <= input; i++)
    {
        gets(dosen[i].code); gets(dosen[i].name); gets(dosen[i].gender); scanf("%d", &(dosen[i].student)); getchar();

        for (j = 1; j <= dosen[i].student; j++)
        {
            gets(dosen[i].mahasiswa[j].code); gets(dosen[i].mahasiswa[j].name); gets(dosen[i].mahasiswa[j].gender);

            gets(dosen[i].mahasiswa[j].father); gets(dosen[i].mahasiswa[j].mother); scanf("%d", &(dosen[i].mahasiswa[j].sibling));
            
            getchar();
        }
    }
    int target; scanf("%d", &target); getchar();

    printf("Kode Dosen: %s\n", dosen[target].code);
        
    printf("Nama Dosen: %s\n", dosen[target].name);
        
    printf("Gender Dosen: %s\n", dosen[target].gender);
        
    printf("Jumlah Mahasiswa: %d\n", dosen[target].student);

    for (int i = 1; i <= dosen[target].student; i++)
    {
        printf("Kode Mahasiswa: %s\n", dosen[target].mahasiswa[i].code);
            
        printf("Nama Mahasiswa: %s\n", dosen[target].mahasiswa[i].name);
            
        printf("Gender Mahasiswa: %s\n", dosen[target].mahasiswa[i].gender);
            
        printf("Nama Ayah: %s\n", dosen[target].mahasiswa[i].father);
            
        printf("Nama Ibu: %s\n", dosen[target].mahasiswa[i].mother);
            
        printf("Jumlah Saudara Kandung: %d\n", dosen[target].mahasiswa[i].sibling);
    }
}

void prob1D()
{
    double number; scanf("%lf", &number);

    printf("%.0lf = %.0lf + %.0lf\n", number, floor(number / 2), ceil(number / 2));
}

void prob1E()
{
    int input, i; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        char input = '0'; int index = 1, sum = 0;

        while (input != '\n')
        {
            sum = (index++ % 2) ? sum - input + '0' : sum + input - '0';

            scanf("%c", &input);
        }
        printf("Case #%d: %s\n", i, !(sum % 11) ? "Yeah" : "Nah");
    }
}

void prob2A()
{
    FILE * fp; int a, b;

    fp = fopen ("testdata.in", "r");

    while (fscanf(fp, "%d %d", &a, &b) != EOF)
    {
        printf("%d\n", a + b);
    }
    fclose(fp);
}

void prob2B()
{
    FILE * fp; int input, i, j, k;

    fp = fopen ("testdata.in", "r");

    while (fscanf(fp, "%d", &input) != EOF)
    {
        for (i = 0; i < input; i++)
        {
            char string[110]; int number, source[26] = {}, alpha[26] = {};
            
            fscanf(fp, "%s\n%d\n", string, &number);

            for (j = 0; j < strlen(string); j++) alpha[string[j] - 65]++;

            for (j = 0; j < number; j++)
            {
                char a, b; fscanf(fp, "%c %c\n", &a, &b);

                if (!source[a - 65])
                {
                    alpha[b - 65] += alpha[a - 65]; alpha[a - 65] = 0; source[a - 65]++;
                }
            }
            for (j = 0; j < 26; j++)
            {
                if (alpha[j]) printf("%c %d\n", j + 65, alpha[j]);
            }
        }
    }
    fclose(fp);
}

void prob2C()
{
    FILE *fp; int input, i, j, k;

    fp = fopen ("testdata.in", "r");

    while (fscanf(fp, "%d\n", &input) != EOF)
    {
        for (i = 1; i <= input; i++)
        {
            int number, value, perimeter = 0, area = 0;
            
            fscanf(fp, "%d\n", &number); int values[number];

            for (j = 0; j < number; j++)
            {
                fscanf(fp, "%d", &values[j]);

                if (j >= 1) { perimeter += 2 * abs(values[j] - values[j - 1]); }

                area += (values[j] * 4);
            }
            perimeter += 2 * (values[0] + values[number - 1] + (2 * number));

            printf("Case #%d: %d %d\n", i, perimeter, area);
        }
    }
    fclose(fp);
}

void prob2D()
{
    FILE * fp; int input, i, j;

    fp = fopen ("testdata.in", "r");

    while (fscanf(fp, "%d\n", &input) != EOF)
    {
        for (i = 1; i <= input; i++)
        {
            int shift; fscanf(fp, "%d\n", &shift);

            char string[1005]; fscanf(fp, "%[^\n]", string);

            for (j = 0; j < strlen(string); j++)
            {
                switch (string[j])
                {
                    case '0': string[j] = 'O'; break;
                    case '1': string[j] = 'I'; break;
                    case '3': string[j] = 'E'; break;
                    case '4': string[j] = 'A'; break;
                    case '5': string[j] = 'S'; break;
                    case '6': string[j] = 'G'; break;
                    case '7': string[j] = 'T'; break;
                    case '8': string[j] = 'B'; break;
                }
                int move = string[j] - shift;

                string[j] = string[j] == ' ' ? ' ' : move < 65 ? 26 + move : move;
            }
            printf("Case #%d: %s\n", i, string);
        }
    }
    fclose(fp);
}

void prob2E()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int n; scanf("%d", &n); getchar(); int values[n + 1];

        for (j = 1; j <= n; j++) scanf("%d", &values[j]);

        printf("Case #%d:\n", i); partition(values, n, 1, values[1]);
    }
}

void prob3A()
{
    int input, i; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int hour, minute; char time[5];
        
        scanf("%d:%d %s", &hour, &minute, time); getchar();

        printf("Case #%d: ", i);

        if (time[0] == 'a') printf("%02d:%02d\n", hour >= 12 ? hour - 12 : hour, minute);

        if (time[0] == 'p') printf("%02d:%02d\n", hour < 12 ? hour + 12 : hour, minute);
    }
}

void prob3B()
{
    double input; scanf("%lf", &input); getchar();

    printf("%lld\n", (long long int)pow(2, input) - 1);
}

void prob3C()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        long long number; scanf("%lld", &number); getchar();

        printf("Case #%d: ", i);
        
        long long int result[64], stat = 0;
        
        while (number > 0) { result[stat++] = number % 2; number /= 2; }
        
        for (j = stat - 1; j >= 0; j--) printf("%d", result[j]);

        printf("\n");
    }
}

void prob3D()
{
    int input, i, j, k; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int size; scanf("%d", &size); int values[size][size];

        for (j = 0; j < size; j++)
        {
            for (k = 0; k < size; k++) scanf("%d", &values[j][k]);
        }
        printf("Case #%d:", i);

        for (j = 0; j < size; j++)
        {
            int result = 0;

            for (k = 0; k < size; k++) result += values[k][j];

            printf(" %d", result);
        }
        printf("\n");
    }
}

void prob3E()
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

                if (values[j][k] == 'P') { posX = j; posY = k; }
            }
            getchar();
        }
        pacmon(values, posX, posY);
        
        printf("Case #%d: %d\n", i, paccount);
    }
}

void prob4A()
{
    int sizeA, sizeB; scanf("%d %d", &sizeA, &sizeB); getchar();
    
    int valuesA[sizeA + 1]; valuesA[0] = 0;

    for (int i = 1; i <= sizeA; i++) scanf("%d", &valuesA[i]);

    for (int i = 1; i <= sizeB; i++)
    {
        int target; scanf("%d", &target);

        int position = 1;

        while (position < sizeA && valuesA[position] < target) position *= 2;

        int index = -1, left = position / 2, right = position > sizeA ? sizeA : position;
        
        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (valuesA[mid] == target) { index = mid; }

            if (valuesA[mid] < target) left = mid + 1;

            else right = mid - 1;
        }
        printf("%d\n", index);
    }
}

void prob4B_1()
{
    int i, j;

    struct database { char friend[105], tree[105]; } data[105];

    FILE *fp = fopen("testdata.in", "r");

    while (!feof(fp))
    {
        int input; fscanf(fp, "%d\n", &input);

        for (i = 1; i <= input; i++)
        {
            fscanf(fp, "%[^#]#%[^\n]\n", data[i].friend, data[i].tree);
        }
        int number; fscanf(fp, "%d\n", &number);

        for (i = 1; i <= number; i++)
        {
            char name[105]; fscanf(fp, "%[^\n]\n", name);

            int status = 0;

            for (j = 1; j <= input; j++)
            {
                if (strcmp(name, data[j].friend) == 0)
                {
                    printf("Case #%d: %s\n", i, data[j].tree);
                    
                    status = 1; break;
                }
            }
            if (status == 0) printf("Case #%d: N/A\n", i);
        }
    }
    
    fclose(fp);
}

void prob4B_2()
{
    //s
}

void prob4C()
{
    int input, i, j; scanf("%d", &input); getchar();

    long long int value, cumulative[100005] = {};

    for (i = 1; i <= input; i++)
    {
        scanf("%lld", &value);
        
        cumulative[i] = (value + cumulative[i - 1]);
    }
    int number; scanf("%d", &number); getchar();

    for (i = 1; i <= number; i++)
    {
        long long int target; scanf("%lld", &target);

        int position = 1;

        while (position < input && cumulative[position] < target) position *= 2;

        int index = -1, left = !(position / 2) ? 1 : (position / 2), right = position > input ? input : position;

        while (left <= right)
        {
            int middle = (left + right) / 2;

            if (cumulative[middle] == target) { index = middle; break; }

            else if (cumulative[middle] < target)
            {
                if ((middle + 1 <= input) && (cumulative[middle + 1] > target)) { index = middle; break; }

                else if (middle + 1 > input) { index = middle; break; }

                left = middle + 1;
            }
            else right = middle - 1;
        }
        printf("Case #%d: %d\n", i, index);
    }
}

void prob4D()
{
    int input, i, j; scanf("%d", &input);

    for (i = 1; i <= input; i++)
    {
        long long int numbers[26] = {}, result[6] = {}, total = 0;

        for (j = 1; j <= 25; j++) { scanf("%lld", &numbers[j]); total += numbers[j]; }

        qsort(numbers, 26, sizeof(long long int), compare);

        result[1] = numbers[1] / 2, result[5] = numbers[25] / 2;

        result[2] = numbers[2] - result[1], result[4] = numbers[24] - result[5];
        
        result[3] = (total / 10) - (result[1] + result[2] + result[4] + result[5]);

        printf("Case #%d:", i);

        for (j = 1; j <= 5; j++) printf(" %lld", result[j]);

        printf("\n");
    }
}

void prob4E()
{
    int input, i, j, k; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        long long int size, value, target, max = -1;
        
        scanf("%lld %lld", &size, &target); getchar();
        
        long long int cumulative[10005] = {};

        for (j = 1; j <= size; j++)
        {
            scanf("%lld", &value);
            
            cumulative[j] += (value + cumulative[j - 1]);
        }
        for (j = 0; j < size; j++)
        {
            for (k = j + 1; k <= size; k++)
            {
                if (cumulative[k] - cumulative[j] <= target)
                {
                    max = (k - j) >= max ? (k - j) : max;
                }
            }
        }
        printf("Case #%d: %lld\n", i, max);
    }
}

void prob5A()
{
    int input, i, j; scanf("%d", &input); getchar();

    int star, x = 0, s = 0;
	
	for (star = pow(2, input) - 1; star >= 1; star /= 2)
    {
        int spaces = pow(2, x) - 1; x++;

		for (i = 0; i < star; i++)
        {
			for (j = 0; j < spaces; j++) printf(" ");

			printf("*");
		}
		printf("\n");
	}
}

void prob5B()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int min = 1000001, values[105] = {};

        int number; scanf("%d", &number);

        for (j = 0; j < number; j++) scanf("%d", &values[j]);

        qsort(values, number, sizeof(int), compare);

        for (j = 1; j < number; j++) min = (values[j] - values[j - 1]) < min ? (values[j] - values[j - 1]) : min;

        printf("Case #%d: %d\n", i, min);
    }
}

void prob5C()
{
    int m, n; scanf("%d %d", &m, &n);

    printf("%d\n", lilieq(m, n));
}

void prob5D()
{
    int input, i, j; scanf("%d", &input); getchar();

    for (i = 1; i <= input; i++)
    {
        int length, target; scanf("%d %d", &length, &target); getchar();

        char names[105][105] = {};

        for (j = 1; j <= length; j++) gets(names[j]);
        
        mergesort(names, 1, length);

        printf("Case #%d: %s\n", i, names[target]);
    }
}