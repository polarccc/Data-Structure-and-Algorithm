#include <stdio.h>

int main() {
    double array[100]; // 假设包括100个实数的数组
    int maxIndex = 0; // 最大元素的位置
    double maxValue = array[0]; // 最大元素的值

    for (int i = 1; i < 100; i++) {
        if (array[i] > maxValue) {
            maxValue = array[i];
            maxIndex = i;
        }
    }

    printf("The max value is: %lf\n", maxValue);
    printf("The index of the max value is: %d\n", maxIndex);

    return 0;
}