#include<stdio.h>
#include<stdlib.h>
#include"sort.h"



void partationSort(int tosort[],int low,int high)
{
	int i=low , j=high;
	int temp;
	temp = *(tosort+i);

	if(i > j)
	{
		return;
	}	

	while(i!=j)
	{
		while(tosort[j]>temp && j>i)
		{
			j--;
		}
		
		while(tosort[i]<=temp && j>i)
		{
			i++;
		}

		if(j>i)
		{
		   	int temp1 = tosort[j];
			tosort[j] = tosort[i];
      			tosort[i] = temp1;
		}
	}
	*(tosort+low)=*(tosort+i);
	*(tosort+i)=temp;

	partationSort(tosort,low,i-1);
	partationSort(tosort,i+1,high);
}
