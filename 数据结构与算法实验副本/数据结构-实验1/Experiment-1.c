#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 1000
#define MAX_FILENAME_LENGTH 100

typedef struct
{
    char data[MAX_EXPRESSION_LENGTH];   //数据域
    int top;                            //栈顶
}Stack;//定义栈结构

void initStack(Stack *stack)//初始化栈
{
    stack->top = -1;
}

void Readfile(char expression[])//进行从文件读入的操作
{
    FILE *file;
    //char filename[MAX_FILENAME_LENGTH];//要打开的文件名，长度不超过100
    char ch;                //从文件中逐个读取字符
    int start_found = 0;    //是否找到开始符
    int end_found = 0;      //是否找到结束符
    int i = 0;

    file = fopen("1.txt", "r");//以只读模式打开文件

    if (file == NULL)
    {
        printf("Open file failed!\n");
        return ;
    }

    while ((ch = fgetc(file)) != EOF)//逐字符读取文件
    {
        if (ch == '#')
        {
            if (start_found == 0)
            {
                start_found = 1;
                continue;//跳出本次循环，即从#后的第一个元素开始读入
            }
            else
            {
                end_found = 1;
                break; //找到结束符，结束循环
            }
        }
        if (start_found)//在找到起始符的情况下开始逐字符读入表达式
        {
            expression[i] = ch;
            i++;
        }
    }
    
    expression[i] = '\0';// 添加字符串结束符
    
    fclose(file);// 关闭文件，防止内存泄露

    if (start_found && end_found)//同时找到起止符
    {
        printf("Expression is : %s\n", expression);
    }
    else
    {
        printf("Incorrect # !\n");
    }

}

void WriteFile(char infixExpression[], char postfixExpression[], int result)//进行写入文件的操作
{
    FILE *file = fopen("result.txt", "w");//只写模式向文件写入数据
    if (file != NULL)
    {
        fprintf(file, "infixExpression:%s\n", infixExpression);
        fprintf(file, "postfixExpression: %s\n", postfixExpression);
        fprintf(file, "Expression result: %d\n", result);
        fclose(file); // 关闭文件以防内存泄露
        printf("Expression saved in expression.txt\n");
    }
    else
    {
        printf("Failed to save expression in file!\n");
    }
}

void push(Stack *stack, char c)//入栈
{
    if (stack->top < MAX_EXPRESSION_LENGTH - 1)
    {
        stack->top++;
        stack->data[stack->top] = c;
        printf("%c pushed\n", c);
    }
    else
    {
        printf("Full Stack, push failed!\n");
    }
}

char pop(Stack *stack)// 出栈
{
    if (stack->top >= 0)
    {
        char c = stack->data[stack->top];
        stack->top--;
        printf("%c poped\n", c);
        return c;
    }
    else
    {
        printf("Empty Stack, pop failed!\n");
        return '\0'; // 返回空字符表示栈已空
    }
}

int getOperatorPriority(char op)//检查运算符的优先级
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0; // 如果不是运算符，返回0
}

void infixToPostfix(char *infixExpression, char *postfixExpression)//将中缀表达式转换为后缀表达式
{
    Stack operatorStack;
    initStack(&operatorStack);

    int infixLength = strlen(infixExpression);
    int postfixIndex = 0;

    for (int i = 0; i < infixLength; i++)
    {
        char currentChar = infixExpression[i];

        if (currentChar >= '0' && currentChar <= '9')
        {
            // 如果是数字，直接输出到后缀表达式
            postfixExpression[postfixIndex++] = currentChar;
        }
        else if (currentChar == '(')
        {
            // 如果是左括号，入栈
            push(&operatorStack, currentChar);
        }
        else if (currentChar == ')')
        {
            // 如果是右括号，出栈并输出运算符到后缀表达式，直到遇到左括号
            while (operatorStack.top >= 0 && operatorStack.data[operatorStack.top] != '(')
            {
                postfixExpression[postfixIndex++] = pop(&operatorStack);
            }
            if (operatorStack.top >= 0 && operatorStack.data[operatorStack.top] == '(')
            {
                pop(&operatorStack); // 弹出左括号
            }
            else
            {
                printf("表达式语法错误：括号不匹配\n");
                return;
            }
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')
        {
            // 如果是运算符
            while (operatorStack.top >= 0 && getOperatorPriority(operatorStack.data[operatorStack.top]) >= getOperatorPriority(currentChar))
            {
                // 如果栈顶运算符优先级大于等于当前运算符，出栈并输出到后缀表达式
                postfixExpression[postfixIndex++] = pop(&operatorStack);
            }
            // 当前运算符入栈
            push(&operatorStack, currentChar);
        }
        else
        {
            printf("Error:illegal input!\n");
            return;
        }
    }

    // 将栈中剩余的运算符输出到后缀表达式
    while (operatorStack.top >= 0)
    {
        if (operatorStack.data[operatorStack.top] == '(')
        {
            printf("bracket not compare!\n");
            return;
        }
        postfixExpression[postfixIndex++] = pop(&operatorStack);
    }

    // 添加字符串结束符
    postfixExpression[postfixIndex] = '\0';
}

// 计算后缀表达式的值
int evaluatePostfixExpression(char *postfixExpression)
{
    Stack operandStack;
    initStack(&operandStack);

    int postfixLength = strlen(postfixExpression);

    for (int i = 0; i < postfixLength; i++)
    {
        char currentChar = postfixExpression[i];

        if (currentChar >= '0' && currentChar <= '9')
        {
            // 如果是数字字符，将其转换为整数并入栈

            // int operand = currentChar - '0';
            // push(&operandStack, operand);

            push(&operandStack, currentChar);
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/')
        {
            // 如果是运算符，从栈中弹出两个操作数并执行运算
            // int operand2 = pop(&operandStack);
            // int operand1 = pop(&operandStack);

            int operand2 = pop(&operandStack) - '0';
            int operand1 = pop(&operandStack) - '0';

            int result;
            char charResult;
            switch (currentChar)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0)
                {
                    printf("Error:divide zero!\n");
                    return 0;
                }
                result = operand1 / operand2;
                break;
            default:
                break;
            }

            // 将运算结果入栈
            charResult = result + '0';
            push(&operandStack, charResult);

            // push(&operandStack, result);
        }
    }

    // 返回最终结果
    return pop(&operandStack);
}

int main()
{
    char infixExpression[MAX_EXPRESSION_LENGTH];
    char postfixExpression[MAX_EXPRESSION_LENGTH];

    printf("Input infixExpression:\n");
    Readfile(infixExpression);
    // scanf("%s", infixExpression);

    infixToPostfix(infixExpression, postfixExpression);

    printf("postfixExpression: %s\n", postfixExpression);

    // 计算后缀表达式的值
    int result = evaluatePostfixExpression(postfixExpression) - '0';// 计算后缀表达式的值,并转换成数字整型

    printf("Expression result: %d\n", result);

    WriteFile(infixExpression,postfixExpression,result);

    return 0;
}

