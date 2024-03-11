#include<stdio.h>
#include<stdlib.h>
#include"arithmetic_calculator.h"

void Read(char *a)
{
	int i = 0;
    	FILE *fp = fopen("arithmetic_expression.txt", "r");
    	if (fp == NULL)
    	{
        	printf("fail to open!\n");
    	}
    	else
    	{
        	fscanf(fp,"%s",a);
       	 	fclose(fp);
    	}
}
