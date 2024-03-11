#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define N 100

void random()
{
    FILE *file = fopen("data.txt", "w");
    int n, n1, n2;
    srand(time(0)); // 设置随机数种子

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前系统时间

    srand(ts.tv_nsec); // 使用纳秒部分作为种子值

    // 生成随机数
    n1 = rand() % 1001;
    n2 = rand() % 101;
    n = n1 * 100 + n2;

    fprintf(file, "%d\n", n);

    // 生成随机序列（每个元素 <10000）
    
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 10001;
        fprintf(file, "%d ", num);
    }
    
    printf("%d random number success\n", n);
    fclose(file);
}

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
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
        fprintf(file, "k%dk ", i);
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
    for (int i = 0; i < N; i++) // 循环生成100次
    {
        //random();

        int size;
        FILE *file = fopen("data.txt", "r");
        fscanf(file, "%d", &size);
        int arr[size];

        for (int i = 0; i < size; i++)
        {
            fscanf(file, "%d", &arr[i]);
        }

        double startTime = getCurrentTime();

        mergeSort(arr, 0, size-1);

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

