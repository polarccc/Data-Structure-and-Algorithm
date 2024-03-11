#include <stdio.h>

void HanoiTower(int n, char source, char auxiliary, char target)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", source, target);
        return;
    }
    HanoiTower(n - 1, source, target, auxiliary);
    //将上面 n-1 个圆盘从源柱子移动到辅助柱子，以目标柱子作为辅助
    printf("Move disk %d from %c to %c\n", n, source, target);
    //输出移动的指令，将第 n 号圆盘从源柱子移动到目标柱子
    HanoiTower(n - 1, auxiliary, source, target);
    //将之前移动到辅助柱子上的 n-1 个圆盘，从辅助柱子移动到目标柱子，以源柱子作为辅助
}
//汉诺塔的递归算法 时间复杂度：o(2^n) 空间复杂度：o(n)

int main()
{
    int n; //圆盘的数量
    printf("input the number of plates:");
    scanf("%d",&n);
    HanoiTower(n, 'A', 'B', 'C'); // 从柱A移动到柱C，借助柱B
        
    return 0;
}
