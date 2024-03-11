#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define max 100


typedef struct arithmetic_calculator
{
	char *base;
	char *top;
	int stacksize;	
}stack;




extern char num[max*2];

extern int count;

extern float num2[max];

extern char result[max];







void Read(char *a);

stack *Initial_stack();

void Change(stack *s,char *a,int len);

void stackpush(stack *s,char a);

char stackgettop(stack *s);

void stackpop(stack *s);

int isempty(stack *s);

int is_num(char a);

void MakeNULL(stack *s);

void arr2num(int len);

void Change2(stack *s,int len);

float cal(float a,char ch,float b);
