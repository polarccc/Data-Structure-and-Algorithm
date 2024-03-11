#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10//字符串最大长度
#define NUM 8//字符串数量

typedef struct node
{
    char data[LEN];
    struct node *next;
} NODE;

void DictionarySort(NODE *head)
{
    NODE *L = (NODE *)malloc(sizeof(NODE)); // 创建空节点
    NODE tmp;
    NODE *p, *q;
    L->next = head;
    for (p = L->next; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if (strcmp(p->data, q->data) < 0)
            {
                strcpy(tmp.data, p->data);
                strcpy(p->data, q->data);
                strcpy(q->data, tmp.data);
            }
        }
    }
}

void DisplayNode(NODE *head)
{
    NODE *p = head->next;
    printf("After sort:\n");
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }
}

int main()
{
    NODE *head = (NODE *)malloc(sizeof(NODE));
    NODE *p = head;
    memset(p->data, 0, LEN);
    for (int i = 0; i < NUM; i++)
    {
        p->next = (NODE *)malloc(sizeof(NODE));
        scanf("%s", p->data);
        p = p->next;
    }
    p->next = NULL;

    DictionarySort(head);
    DisplayNode(head);

    return 0;
}