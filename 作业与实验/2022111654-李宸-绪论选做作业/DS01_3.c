#include <stdio.h>
#include <stdbool.h>
#define MAX_PLAYERS 100

int n; // n个选手

struct Player
{
    int id;//选手id
    bool used;//选手是否已排序
    int score;//用于比较的参数
}; // 定义选手结构体

int beats(struct Player a, struct Player b)// 检查选手是否胜过另一个选手
{
    return a.score > b.score;// 返回1表示a胜过b，0相反
}

int findSequence(struct Player players[], struct Player currentSequence[], int index)// 回溯函数，尝试生成符合条件的选手序列
{
    if (index == n)// 检查最后一个选手是否胜过第一个选手
    {
        if (beats(currentSequence[index - 1], currentSequence[0]))
        {
            return 1;
        }
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (!players[i].used)// 如果该选手还未被排序
        {
            currentSequence[index] = players[i];
            players[i].used = 1;

            if (findSequence(players, currentSequence, index + 1))// 递归生成下一个选手
            {
                return 1;
            }

            players[i].used = 0;// 条件不成立，取消选择
        }
    }

    return 0;
}

int main()
{

    struct Player players[MAX_PLAYERS];
    for (int i = 0; i < n; i++)
    {
        players[i].id = i + 1;
        players[i].used = 0;
    }

    struct Player currentSequence[MAX_PLAYERS];

    if (findSequence(players, currentSequence, 0))
    {
        printf("Find the satisfying player order:\n");
        for (int i = 0; i < n; i++)
        {
            printf("P%d ", currentSequence[i].id);
        }
        printf("\n");
    }
    else
    {
        printf("Falied to find the satisfying player order!\n");
    }

    return 0;
}