#include <stdio.h>
#include <stdlib.h>

#define SIZE 100//数组的最大长度

typedef struct{
    int data[SIZE];//数组存储数据
    int length;//线性表的长度
}Seqlist;

void InputSeqlist(Seqlist *list) {
    int n;
    printf("Input the length of Seqlist:");
    scanf("%d", &n);

    if (n > SIZE) {
        printf("Input error!\n");//线性表长度超过最大容量
        return;
    }

    printf("Input the elements one by one: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &(list->data[i]));
    }

    list->length = n;
}

void PrintSeqlist(Seqlist *list) {
    if (list->length == 0) {
        printf("Empty list!\n");
        return;
    }

    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
}

int DeleteElement(Seqlist *list, int element)
{
    int found;//是否找到待删元素
    for (int i = 0; i < list->length; i++)
    {
        if (list->data[i] == element)
        {
            found = 1;
            // printf("Delete success!");
            for (int j = i + 1; j < list->length; j++)
            {
                list->data[j - 1] = list->data[j];
            }
            list->length--;
            i--; //重新检查当前位置，以防多个相邻相同元素的情况
        }
    }

    return found; //返回是否找到待删除元素的信息
}

int DeleteDuplicates(Seqlist *list)
{
    int delete = 0; // 重复元素可供删除的个数
    if (list->length <= 1)//长度小于等于1，无重复情况
    {
        return 0;
    }
    int unique = 0;
    for (int i = 1; i < list->length; i++)
    {
        if (list->data[i] != list->data[unique])
        {
            unique++;                           // 不是重复元素，唯一元素位置加1
            list->data[unique] = list->data[i]; // 将不同的元素移到唯一元素位置
        }
    }
    delete = list->length - unique - 1;
    list->length = unique + 1;
    //printf("%d",delete);
    return delete;
}

void Reverse(Seqlist *list)
{
    int left = 0;   //左指针
    int right = list->length - 1;   //右指针
    int temp;       //交换data的临时变量
    while (left < right)
    {
        temp = list->data[left];
        list->data[left] = list->data[right];
        list->data[right] = temp;

        left++;
        right--;
    }
}

void LeftShift(Seqlist *list, int k)
{
    k = k % list->length; // 实现循环操作
    int temp[SIZE];       // 临时数组，存放移动后的元素

    for (int i = 0; i < k; i++)
    {
        temp[i] = list->data[i];
    }
    for (int i = k; i < list->length; i++)
    {
        list->data[i - k] = list->data[i];
    }
    for (int i = 0; i < k; i++)
    {
        list->data[list->length - k + i] = temp[i];
    }
}

Seqlist *MergeSortedLists(Seqlist *list1, Seqlist *list2)
{
    int i = 0, j = 0, k = 0; // 表1，表2，新表的指针
    Seqlist *merged = (Seqlist *)malloc(sizeof(Seqlist));

    while (i < list1->length && j < list2->length)
    {
        if (list1->data[i] < list2->data[j])
        {
            merged->data[k] = list1->data[i];
            k++;
            i++;
        }
        else
        {
            merged->data[k] = list2->data[j];
            k++;
            j++;
        }
    }
    while (i < list1->length)
    {
        merged->data[k] = list1->data[i];
        k++;
        i++;
    }
    while (j < list2->length)
    {
        merged->data[k] = list2->data[j];
        k++;
        j++;
    }

    merged->length = k;
    return merged;
}

int main()
{
    Seqlist list,list2;
    
    InputSeqlist(&list);
    //PrintSeqlist(&list);

    int choose;
    printf("Input your choose\n1.DeleteElement 2.DeleteDuplicates 3.Reverse 4.LeftShift 5.MergeSortedLists\n");
    printf("Attention:If you choose 2 or 5, the list must be sorted.\n");
    scanf("%d", &choose);
    switch(choose){
        case 1:
            int element; // 待删除元素
            printf("Input element to delete:\n");
            scanf("%d",&element);
            if(DeleteElement(&list, element)){
                PrintSeqlist(&list);
            }
            else{
                printf("element not exist!\n");
            }
            break;
        case 2:
            printf("After delete %d elements:\n",(DeleteDuplicates(&list)));
            PrintSeqlist(&list);
            break;
        case 3:
            Reverse(&list);
            PrintSeqlist(&list);
            break;
        case 4:
            int k;       // 左移k位
            printf("Input k to leftshift\n");
            scanf("%d",&k);
            LeftShift(&list, k);
            PrintSeqlist(&list);
            break;
        case 5:
            printf("Input another list:\n");
            InputSeqlist(&list2);
            PrintSeqlist(MergeSortedLists(&list,&list2));
            break;
    }

    return 0;
}