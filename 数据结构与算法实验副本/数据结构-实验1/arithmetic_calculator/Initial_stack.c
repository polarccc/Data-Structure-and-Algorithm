#include<stdio.h>
#include<stdlib.h>
#include"arithmetic_calculator.h"

stack *Initial_stack()
{
	stack *s=(stack *)malloc(sizeof(stack));
	s->base = (char *)malloc(sizeof(char)*max);
	s->top = s->base;
	s->stacksize = max;
	return s;
}
