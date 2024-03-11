#include <stdio.h>
#include <stdlib.h>

typedef struct Node// 定义链表节点结构
{
    int data;
    struct Node *next;
}Linklist;

Linklist *initLinkedList()// 初始化链表
{
    return NULL;
}

Linklist *append(Linklist *head, int data)//向表尾添加元素
{
    Linklist *newNode = (Linklist *)malloc(sizeof(Linklist));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)//原链表为空，直接返回新节点
    {
        return newNode;
    }

    Linklist *current = head;
    while (current->next != NULL)//从头指针查找，直到尾指针
    {
        current = current->next;
    }
    current->next = newNode;//在表尾添加新节点

    return head;
}

Linklist *InputLinkedList()//输入元素
{
    Linklist *head = NULL;
    int element;
    printf("Input the elements one by one, input -1 to end:\n");

    while (1)
    {
        scanf("%d", &element);
        if (element == -1)
        {
            break;
        }
        head = append(head, element);
    }
    return head;
}

void PrintLinklist(Linklist *head)//形象地显示链表元素
{
    Linklist *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Linklist *DeleteElement(Linklist *head, int element)//删除指定元素
{
    Linklist *current = head;
    Linklist *prev = NULL;

    if (current != NULL && current->data == element)//如果要删除的元素是链表头元素
    {
        head = current->next;
        free(current);
        return head;
    }
    while (current != NULL && current->data != element)//遍历链表
    {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("%d 不存在于链表中\n", element);
        return head;
    }
    prev->next = current->next;//满足条件，删除current

    free(current);
    return head;
}

Linklist *DeleteDuplicates(Linklist *head)//删除重复元素
{
    if (head == NULL)
    {
        return NULL;
    }

    Linklist *current = head;
    while (current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            Linklist *temp = current->next;
            current->next = temp->next;//删除temp
            free(temp);
        }
        else
        {
            current = current->next;
        }
    }
    return head;
}

Linklist *LeftShift(Linklist *head, int k)//左移k位
{
    if (head == NULL || k == 0)
    {
        return head;
    }
    Linklist *current = head;
    int count = 1;
    while (count < k && current != NULL)
    {
        current = current->next;
        count++;
    }
    if (current == NULL)
    {
        return head; // 如果k大于链表长度，不执行左移操作
    }

    Linklist *newHead = current->next;
    current->next = NULL;

    current = newHead;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = head;
    return newHead;
}

Linklist *Reverse(Linklist *head)//逆置算法
{
    Linklist *prev = NULL;
    Linklist *current = head;
    Linklist *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

Linklist *MergeSortedLists(Linklist *list1, Linklist *list2)//合并两个已排好序的线性表
{
    if (list1 == NULL)
    {
        return list2;
    }
    if (list2 == NULL)
    {
        return list1;
    }

    Linklist *mergedList = NULL;
    Linklist *tail = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data < list2->data)
        {
            if (mergedList == NULL)//头结点的情况
            {
                mergedList = list1;
                tail = list1;
            }
            else
            {
                tail->next = list1;
                tail = list1;
            }
            list1 = list1->next;
        }
        else
        {
            if (mergedList == NULL)
            {
                mergedList = list2;
                tail = list2;
            }
            else
            {
                tail->next = list2;
                tail = list2;
            }
            list2 = list2->next;
        }
    }

    if (list1 != NULL)
    {
        tail->next = list1;
    }
    else
    {
        tail->next = list2;
    }

    return mergedList;
}

int main() {

    Linklist *head = InputLinkedList();

    int choose;
    printf("Input your choose\n1.DeleteElement 2.DeleteDuplicates 3.Reverse 4.LeftShift 5.MergeSortedLists\n");
    printf("Attention:If you choose 2 or 5, the list must be sorted.\n");
    scanf("%d", &choose);
    switch(choose){
        case 1:
            int element; // 待删除元素
            printf("Input element to delete:\n");
            scanf("%d",&element);
            PrintLinklist((DeleteElement(head, element)));
            break;
        case 2:
            PrintLinklist((DeleteDuplicates(head)));
            break;
        case 3:
            PrintLinklist(Reverse(head));
            break;
        case 4:
            int k;       // 左移k位
            printf("Input k to leftshift\n");
            scanf("%d",&k);
            PrintLinklist(LeftShift(head, k));
            break;
        case 5:
            printf("Input another list:\n");
            Linklist* head2=InputLinkedList();
            PrintLinklist(MergeSortedLists(head, head2));
            break;
    }

    return 0;
}
