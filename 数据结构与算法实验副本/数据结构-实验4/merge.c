#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 100

void random()
{
    FILE *file = fopen("data.txt", "w");
    int n, n1, n2, n3;
    srand(time(0)); // 设置随机数种子

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前系统时间

    srand(ts.tv_nsec); // 使用纳秒部分作为种子值

    // 生成随机数
    n1 = rand() % 100001;
    n2 = rand() % 100001;
    n3 = rand() % 100001;
    n = n1 + n2 + n3;

    fprintf(file, "%d\n", n);

    // 生成随机序列（每个元素 <10000）
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 10000;
        fprintf(file, "%d ", num);
    }
    printf("%d random number success\n", n);
}

void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }

    while (i < leftSize)
    {
        arr[k++] = left[i++];
    }

    while (j < rightSize)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int size)
{
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);
    merge(arr, left, mid, right, size - mid);

    free(left);
    free(right);
}

void writeToFile(int arr[], int size, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

double getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main()
{
    for (int i = 0; i < N; i++) // 循环生成50次
    {
        random();

        int size;
        FILE *file = fopen("data.txt", "r");
        fscanf(file, "%d", &size);
        int arr[size];

        for (int i = 0; i < size; i++)
        {
            fscanf(file, "%d", &arr[i]);
        }

        double startTime = getCurrentTime();

        mergeSort(arr, size);

        double endTime = getCurrentTime();

        double elapsedTime = endTime - startTime;

        writeToFile(arr, size, "merge_sorted_sequence.txt");

        printf("已将排序后的序列写入文件 merge_sorted_sequence.txt\n");
        printf("归并排序运行时间：%.6f 秒\n", elapsedTime);

        FILE *timefile = fopen("merge-time.txt", "a");
        fprintf(timefile, "%d %.6f\n", size, elapsedTime);
        fclose(timefile);
    }
    return 0;
}
