#include<stdio.h>
#include<stdlib.h>
#include"arithmetic_calculator.h"

char stackgettop(stack *s)
{
	if(s->base == s->top)
	{
		printf("stack is empty!\n");
		return -1;
	}
	else
	{
		return *(s->top-1);
	}
}

void stackpop(stack *s)
{
	if(s->base == s->top)
        {
                printf("stack is empty!\n");
        }
	else
	{
		s->top = s->top-1;
	}
}

void stackpush(stack *s,char a)
{
	if(s->top-s->base == s->stacksize)
        {
                printf("overflow!\n");
        }

	else
	{
		*(s->top) = a;
		s->top++;
	}
}

int isempty(stack *s)
{
	if(s->base == s->top)
        {
                return 1;
        }
	else
		return 0;
}

void MakeNULL(stack *s)
{
	s->top=s->base;
}
