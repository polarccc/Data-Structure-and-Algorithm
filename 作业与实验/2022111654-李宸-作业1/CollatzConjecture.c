#include <stdio.h>

int CollatzConjecture(int n, int *i)
{
    int orijin = n;
    *i = 0;
    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n = 3 * n + 1;
        }
        (*i)++; // 计数序列长度
        if (n == orijin)// 如果回到了初始值，说明进入了循环，不满足奇偶猜想
        {             
            return 0; //不成立
        }
    }
    return 1; // 成立
}

int main()
{
    int maxLenth = 0;    // 最大序列长度
    int maxLenthNum = 0; // 最大序列长度对应的数
    int false = 0;       // 不成立的个数
    for (int n = 1; n <= 100; n++)
    {
        int i = 0; // 每个n的序列长度
        if (!CollatzConjecture(n, &i))
        {
            false ++;
        }
        else if (i > maxLenth)
        {
            maxLenth = i;
            maxLenthNum = n;
        }
        // CollatzConjecture(n, &i);
    }
    printf("Not satisfying amount:%d\n", false);
    printf("The number of longest steps is %d,with %d steps\n", maxLenthNum, maxLenth);

    return 0;
}