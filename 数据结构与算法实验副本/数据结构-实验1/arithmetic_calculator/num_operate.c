#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"arithmetic_calculator.h"

int is_num(char a)
{
	if ((a >= '0' && a <= '9') || a == '.')
        	return 1;
    	else
        	return 0;
}


void arr2num(int len)
{
	int i,k=0,j=0;
	for(i=0;i<len;i++)
	{
		if(num[i]=='e')
		{
			continue;
		}

		else if(!is_num(num[i]))
		{
			result[k]=num[i];
			k++;	
		}

		else
		{
			int front=0,behind=0,flag=1;
			while(num[i]!='.'&&num[i]!='e')
			{
				front++;
				i++;
			}
 		       	if(num[i]!='e')
     			{
         			flag=0;
				i++;
        		}
			while(num[i]!='e')
			{
				behind++;
				i++;
			}
			int a;
       	 		if(flag==0)
        		{
				for(a=i-1;a>=i-behind;a--)
				{
					num2[j]+=(num[a]-'0')*(float)pow(10,-(behind-i+a+1));
				}
				for(a=a-1;a>=i-behind-front-1;a--)
				{
				  	num2[j]+=(num[a]-'0')*(float)pow(10,front-(a-(i-1-behind-front))-1);
				}
        		}
       	 		else
        		{
          			for(a=i-1;a>=i-front;a--)
          			{
            			num2[j]+=(num[a]-'0')*(float)pow(10,front-(a-(i-front))-1);
          			}	
        		}
			result[k]=j+'0';
			k++;
			j++;	
		}
	}
	printf("%f %f %f %f",num2[0],num2[1],num2[2],num2[3]);
}

float cal(float a,char ch,float b)
{
	float res;
	switch (ch)
	{
	case '+':
		res = a+b;
		break;
	case '-':
		res = a-b;
		break;
	case '*':
		res = a*b;
		break;
	case '/':
		res = a/b;
		break;
	case '^':
		res = (float)pow(a,b);
		break;
	}
	return res;
}
