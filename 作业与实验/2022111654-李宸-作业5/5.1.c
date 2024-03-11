#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateOddNumbers(int n) {
    FILE *file = fopen("odd_numbers.txt", "w");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    for (int i = 1; i <= n; i++) {
        fprintf(file, "%d\n", 2 * i - 1);
    }

    fclose(file);
}

void shuffleNumbers() {
    FILE *inputFile = fopen("odd_numbers.txt", "r");
    FILE *outputFile = fopen("shuffled_numbers.txt", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    int numbers[2048];
    int count = 0;
    int number;

    while (fscanf(inputFile, "%d", &number) != EOF) {
        numbers[count] = number;
        count++;
    }

    for (int i = count - 1; i > 0; i--) {
        srand(time(NULL));
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "%d\n", numbers[i]);
    }

    fclose(inputFile);
    fclose(outputFile);
}

int main() {
    int n = 1024; // 生成奇数的数量

    generateOddNumbers(n);
    shuffleNumbers();

    printf("已生成并打乱奇数。\n");

    return 0;
}
