#include<stdio.h>
#include<stdlib.h>
#include"arithmetic_calculator.h"

void judge_priority(char a,stack *s);
int priority(char a);


void Change(stack *s,char *a,int len)
{
	int i=0,flag=0;
	for(i=0;i<len;i++)
	{
		if(is_num(a[i]))
		{
			printf("Step %d:'%c' is num,output\n",i+1,a[i]);
			num[count] = a[i];
			count++;
			if(!is_num(a[i+1]))
			{
				num[count]='e';
				count++;
			}
		}
		else
		{
			printf("Step %d:'%c' is operator,process\n",i+1,a[i]);
			
			if(a[i]=='#')
			{
				flag++;
				if(flag==2)
				{
					char temp = stackgettop(s);
                                	while(!isempty(s))
                                	{
                                        	num[count]=temp;
                                       		count++;
                                        	printf("'%c' out of stack\n",temp);
                                        	stackpop(s);
                                      	  	temp = stackgettop(s);
                                	}
					printf("over!\n");
					break;
				}
				continue;
			}

			else if(a[i]=='(')
			{
				printf("Highest priority,push it into the stack\n");
				stackpush(s,a[i]);
				continue;
			}

			else if(a[i]==')')
			{
				printf("Lowest priority,pop stack untill meet '('\n");
				char temp = stackgettop(s);
				while(temp!='(')
				{
					num[count]=temp;
					count++;
					printf("'%c' out of stack\n",temp);
					stackpop(s);
					temp = stackgettop(s);
				}
				stackpop(s);
				printf("'(' out of stack\n");
				continue;
			}
			else
			{
				judge_priority(a[i],s);
			}
		}
	}
 printf("%s\n",num);
}


void judge_priority(char a,stack *s)
{
	int p1 = priority(a);
	int p2;
	if(!isempty(s))
	{
		p2 = priority(stackgettop(s));
	}
	else
	{
		p2 = 0;
	}
	if(p2 == 0)
        {
                printf("push '%c' into the empty stack\n",a);
                stackpush(s,a);
        }
	else if(p1>p2)
	{
		printf("'%c' is higher than the top of the stack('%c'),push it into the stack\n",a,stackgettop(s));
		stackpush(s,a);
	}
	else
	{
		do
		{
			printf("'%c' is lower than or equal to the top of the stack('%c'),pop the top out\n",a,stackgettop(s));
			num[count]=stackgettop(s);
			count++;
			stackpop(s);

			if(!isempty(s))
			{
				p2 = priority(stackgettop(s));
			}
			else
			{
				p2 = 0;
			}
		}while(p1<=p2);
		printf("'%c' is higher than the top of the stack('%c'),push it into the stack\n",a,stackgettop(s));
		stackpush(s,a);
	}
}

int priority(char a)
{
	if(a=='+')
	{
		return 1;
	}
	else if(a=='-')
	{
		return 1;
	}
	else if(a=='*')
	{
		return 2;
	}
	else if(a=='/')
	{
		return 2;
	}
	else if(a=='^')
	{
		return 3;
	}
	else
		return 0;
}

void Change2(stack *s,int len)
{
	char ch1,ch2;
	for(int i=0;i<len;i++)
	{
		if(is_num(result[i]))
		{
			printf("step %d: %f is a number,push it into the stack\n",i+1,num2[result[i]-'0']);
			stackpush(s,result[i]);
			continue;
		}
		else
		{
			printf("step %d: '%c' is an operator,calculate!\n",i+1,result[i]);
			ch1 = stackgettop(s);
			stackpop(s);
			ch2 = stackgettop(s);
			stackpop(s);

			float res;
			res = cal(num2[ch2-'0'],result[i],num2[ch1-'0']);
			printf("%.3f %c %.3f = %.3f\n",num2[ch2-'0'],result[i],num2[ch1-'0'],res);
			num2[ch1-'0'] = res;
			stackpush(s,ch1);
			continue;
		}
	}
	printf("Result:%.3f\n",num2[stackgettop(s)-'0']);
}
