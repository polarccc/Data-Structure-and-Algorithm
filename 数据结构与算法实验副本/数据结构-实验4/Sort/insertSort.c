#include<stdio.h>
#include<stdlib.h>
#include"sort.h"


void insertSort(int tosort[],int n)
{
	int k;
	for(int i=1;i<n;i++)
	{
		k = i-1;
		while(tosort[k]>tosort[k+1] && k >= 0)
		{
			int temp = tosort[k];
      tosort[k] = tosort[k+1];
      tosort[k+1] = temp;
			k = k-1;
		}		
	}
}