#include <stdio.h>
#include <math.h>

void BubbleSort(int array[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])    //升序排序
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}
//冒泡排序算法 时间复杂度:o(n^2) 空间复杂度:o(1)

void SelectSort(int array[], int size)
{
    int temp;
    int min; // 最小数的下标
    for (int i = 0; i < size - 1; i++)
    {
        min = i; // 初始化最小数的下标
        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[min])
            {
                min = j; // 更新最小数下标
            }
        }
        temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}
//直接选择排序算法 时间复杂度:o(n^2) 空间复杂度:o(1)

void InsertSort(int array[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++)
    {
        key = array[i];
        j = i - 1; // 移动比key大的元素向右，为key腾出位置
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}
//直接插入排序 时间复杂度:o(n^2) 空间复杂度:o(1)

int main()
{
    int size;
    printf("input array size\n");
    scanf("%d", &size);
    int array[size];
    printf("input array\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    int choose;
    printf("Input your choose\n1.BubbleSort 2.SelectSort 3.InsertSort\n");
    scanf("%d", &choose);
    switch(choose){
        case 1:
            BubbleSort(array, size);
            break;
        case 2:
            SelectSort(array, size);
            break;
        case 3:
            InsertSort(array, size);
            break;
    }
    

    for (int j = 0; j < size; j++)
    {
        printf("%d  ", array[j]);
    }

    return 0;
}