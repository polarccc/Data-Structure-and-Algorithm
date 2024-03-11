#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arithmetic_calculator.h"

char num[max*2];

int count=0;

float num2[max]={0};

char result[max];


int main(int argc,char *argv[])
{
	stack *s=Initial_stack();

	char a[100];
	Read(a);
	printf("Initial:%s\n",a);

	int len;
	len = strlen(a);
	
	Change(s,a,len);

	printf("The postfix expression is: \n");
	for(int i=0;i<count;i++)
	{
		if(num[i]=='e')
		{
			printf(" ");
		}
		else
		{
			if(is_num(num[i]))
			{
				printf("%c",num[i]);
			}
			else
			{
				printf("%c ",num[i]);
			}
		}
	}
	printf("\n");

	int length = strlen(num);
	arr2num(length);
	MakeNULL(s);


	int length2 = strlen(result);
	Change2(s,length2);

	return 0;
}
