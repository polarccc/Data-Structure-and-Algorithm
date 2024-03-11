#include<stdio.h>
#include<stdlib.h>
#include"sort.h"

void selectSort(int tosort[],int n)
{
	int min;
	for(int i=0;i<n-1;i++)
	{
		min = i;
		for(int j=i+1;j<n;j++)
		{
			if(tosort[j]<tosort[min])
			{
				min = j;
			}
		}
		int temp = tosort[i];
   tosort[i] = tosort[min];
   tosort[min] = temp;
	}
}
