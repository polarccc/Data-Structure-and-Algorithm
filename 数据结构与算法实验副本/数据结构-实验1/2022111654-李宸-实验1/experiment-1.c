#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPRESSION_SIZE 100

// 定义操作符栈和结果栈
char operatorStack[MAX_STACK_SIZE];
double valueStack[MAX_STACK_SIZE];
int operatorTop = -1;
int valueTop = -1;

void Readfile(char expression[])//进行从文件读入的操作
{
    FILE *file;
    char ch;                //从文件中逐个读取字符
    int start_found = 0;    //是否找到开始符
    int end_found = 0;      //是否找到结束符
    int i = 0;

    file = fopen("expression.txt", "r");//以只读模式打开文件

    if (file == NULL)
    {
        printf("Open file failed!\n");
        return;
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

void WriteFile(char infixExpression[], char postfixExpression[], double result)//进行写入文件的操作
{
    FILE *file = fopen("result.txt", "w");//只写模式向文件写入数据
    if (file != NULL)
    {
        fprintf(file, "infixExpression:%s\n", infixExpression);
        fprintf(file, "postfixExpression: %s\n", postfixExpression);
        fprintf(file, "Expression result: %.2f\n", result);
        fclose(file); // 关闭文件以防内存泄露
        printf("Expression saved in expression.txt\n");
    }
    else
    {
        printf("Failed to save expression in file!\n");
    }
}

// 定义运算符优先级
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// 执行计算
double applyOperator(char op, double b, double a) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "错误：除数为零\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "错误：未知的运算符 '%c'\n", op);
            exit(EXIT_FAILURE);
    }
}

// 将中缀表达式转换为后缀表达式
void infixToPostfix(const char *infix, char *postfix) {
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i]) || (infix[i] == '.' && isdigit(infix[i + 1]))) {
            // 如果是数字或小数点，将连续的字符组合为一个数
            while (isdigit(infix[i]) || infix[i] == '.') {
                //printf("%c pushed\n" ,infix[i]);
                postfix[postfixIndex++] = infix[i++];
            }
            postfix[postfixIndex++] = ' ';
            i--; // 回退一个字符，以便检测运算符
        } else if (infix[i] == '(') {
            // 如果是左括号，直接入栈
            printf("%c pushed\n" ,infix[i]);
            operatorStack[++operatorTop] = infix[i];
        } else if (infix[i] == ')') {
            // 如果是右括号，弹出操作符栈中的操作符并加入后缀表达式，直到遇到左括号
            while (operatorTop >= 0 && operatorStack[operatorTop] != '(') {
                printf("%c poped\n" ,operatorStack[operatorTop]);
                postfix[postfixIndex++] = operatorStack[operatorTop--];
                postfix[postfixIndex++] = ' ';
            }
            // 弹出左括号
            if (operatorTop >= 0 && operatorStack[operatorTop] == '(') {
                printf("( poped\n");
                operatorTop--;
            } else {
                fprintf(stderr, "错误：括号不匹配\n");
                exit(EXIT_FAILURE);
            }
        } else if (infix[i] == ' ' || infix[i] == '\t') {
            // 忽略空格和制表符
            continue;
        } else {
            // 如果是运算符，比较运算符优先级，如果栈顶运算符优先级大于等于当前运算符，出栈并输出到后缀表达式
            while (operatorTop >= 0 && operatorStack[operatorTop] != '(' && getPrecedence(infix[i]) <= getPrecedence(operatorStack[operatorTop])) {
                printf("%c poped\n" ,operatorStack[operatorTop]);
                postfix[postfixIndex++] = operatorStack[operatorTop--];
                postfix[postfixIndex++] = ' ';
            }
            printf("%c pushed\n" ,infix[i]);
            operatorStack[++operatorTop] = infix[i];
        }
    }

    // 将操作符栈中的剩余操作符加入后缀表达式
    while (operatorTop >= 0) {
        if (operatorStack[operatorTop] == '(' || operatorStack[operatorTop] == ')') {
            fprintf(stderr, "错误：括号不匹配\n");
            exit(EXIT_FAILURE);
        }
        printf("%c poped\n" ,operatorStack[operatorTop]);
        postfix[postfixIndex++] = operatorStack[operatorTop--];
        postfix[postfixIndex++] = ' ';
    }

    postfix[postfixIndex] = '\0';
}

// 计算后缀表达式的值
double evaluatePostfix(const char *postfix) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i]) || (postfix[i] == '.' && isdigit(postfix[i + 1]))) {
            // 如果是数字或小数点，将连续的字符组合为一个数并入栈
            char numStr[MAX_STACK_SIZE];
            int numStrIndex = 0;
            while (isdigit(postfix[i]) || postfix[i] == '.') {
                numStr[numStrIndex++] = postfix[i++];
            }
            numStr[numStrIndex] = '\0';
            double num = atof(numStr);
            printf("%.2f poped\n",num);
            valueStack[++valueTop] = num;
            i--; // 回退一个字符，以便检测运算符
        } else if (postfix[i] == ' ') {
            // 忽略空格
            continue;
        } else {
            // 如果是运算符，弹出栈顶的两个数进行计算，并将结果入栈
            double b = valueStack[valueTop--];
            double a = valueStack[valueTop--];
            printf("%.2f ,%.2f poped\n",b,a);
            double result = applyOperator(postfix[i], b, a);
            printf("%.2f pushed\n",result);
            valueStack[++valueTop] = result;
        }
    }

    // 最终栈中应只剩下一个结果
    if (valueTop == 0) {
        return valueStack[valueTop];
    } else {
        fprintf(stderr, "错误：操作数不匹配\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char infixExpression[MAX_EXPRESSION_SIZE];
    char postfixExpression[MAX_EXPRESSION_SIZE];

    Readfile(infixExpression);

    infixToPostfix(infixExpression, postfixExpression);
    printf("后缀表达式：%s\n", postfixExpression);

    double result = evaluatePostfix(postfixExpression);
    printf("计算结果：%.2f\n", result);

    WriteFile(infixExpression,postfixExpression,result);

    return 0;
}
