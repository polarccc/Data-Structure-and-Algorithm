#include <stdio.h>
#include <stdlib.h>

// 折半查找算法
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[] = {56, 2, 38, 16, 8, 72, 23, 91, 12, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target;
    
    scanf("%d",&target);
    // 对数组进行排序
    qsort(arr, n, sizeof(int), compare);

    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1) {
        printf("未找到目标元素\n");
    } else {
        printf("目标元素在数组中的索引为 %d\n", result);
    }

    return 0;
}
