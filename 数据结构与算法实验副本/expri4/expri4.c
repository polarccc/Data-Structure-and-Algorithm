#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void random()
{
    FILE *file = fopen("data.txt", "w");
    int n;
    srand(time(0)); // 设置随机数种子

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts); // 获取当前系统时间

    srand(ts.tv_nsec); // 使用纳秒部分作为种子值

    // 生成随机数
    n = rand() % 100001;


    fprintf(file, "%d\n", n);

    // 生成随机序列（每个元素 <10000）
    for (int i = 0; i < n; i++)
    {
        int num = rand() % 10000;
        fprintf(file, "%d ", num);
    }
    printf("%d random number success\n", n);
}
/*
int main() {
    
    random();

    return 0;
}
*/