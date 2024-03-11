#include <stdio.h>
#include <stdlib.h>

// 定义一个栈结构
struct Stack {
    int capacity; // 栈的容量
    int top;      // 栈顶指针
    int *array;   // 存储元素的数组
};

// 创建一个新的栈
struct Stack *createStack(int capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(capacity * sizeof(int));
    return stack;
}

// 检查栈是否为空
int isEmpty(struct Stack *stack) {
    return (stack->top == -1);
}

// 将元素压入栈
void push(struct Stack *stack, int item) {
    stack->array[++stack->top] = item;
}

// 从栈中弹出元素
int pop(struct Stack *stack) {
    return stack->array[stack->top--];
}

// 非递归实现汉诺塔
void iterativeHanoi(int n, char source, char auxiliary, char target) {
    struct Stack *sourceStack = createStack(n);
    struct Stack *auxiliaryStack = createStack(n);
    struct Stack *targetStack = createStack(n);
    int totalMoves = (1 << n) - 1; // 计算总共需要的移动次数

    // 初始化源柱子
    for (int i = n; i >= 1; i--) {
        push(sourceStack, i);
    }

    // 如果n为奇数，交换辅助柱子和目标柱子
    if (n % 2 == 1) {
        char temp = auxiliary;
        auxiliary = target;
        target = temp;
    }

    // 执行非递归汉诺塔算法
    for (int move = 1; move <= totalMoves; move++) {
        if (move % 3 == 1) {
            // 第一步：从源柱子移动到目标柱子
            if (!isEmpty(sourceStack) && (isEmpty(targetStack) || sourceStack->array[sourceStack->top] < targetStack->array[targetStack->top])) {
                int disk = pop(sourceStack);
                printf("Move disk %d from %c to %c\n", disk, source, target);
                push(targetStack, disk);
            } else {
                int disk = pop(targetStack);
                printf("Move disk %d from %c to %c\n", disk, target, source);
                push(sourceStack, disk);
            }
        } else if (move % 3 == 2) {
            // 第二步：从源柱子移动到辅助柱子
            if (!isEmpty(sourceStack) && (isEmpty(auxiliaryStack) || sourceStack->array[sourceStack->top] < auxiliaryStack->array[auxiliaryStack->top])) {
                int disk = pop(sourceStack);
                printf("Move disk %d from %c to %c\n", disk, source, auxiliary);
                push(auxiliaryStack, disk);
            } else {
                int disk = pop(auxiliaryStack);
                printf("Move disk %d from %c to %c\n", disk, auxiliary, source);
                push(sourceStack, disk);
            }
        } else {
            // 第三步：从辅助柱子移动到目标柱子
            if (!isEmpty(auxiliaryStack) && (isEmpty(targetStack) || auxiliaryStack->array[auxiliaryStack->top] < targetStack->array[targetStack->top])) {
                int disk = pop(auxiliaryStack);
                printf("Move disk %d from %c to %c\n", disk, auxiliary, target);
                push(targetStack, disk);
            } else {
                int disk = pop(targetStack);
                printf("Move disk %d from %c to %c\n", disk, target, auxiliary);
                push(auxiliaryStack, disk);
            }
        }
    }

    // 释放栈内存
    free(sourceStack->array);
    free(sourceStack);
    free(auxiliaryStack->array);
    free(auxiliaryStack);
    free(targetStack->array);
    free(targetStack);
}

int main() {
    int n = 3; // 设置汉诺塔的圆盘数量
    char source = 'A';
    char auxiliary = 'B';
    char target = 'C';

    printf("Moves to solve the Hanoi Tower problem:\n");
    iterativeHanoi(n, source, auxiliary, target);

    return 0;
}
