#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sort.h"

static void _mergeSort(int tosort[],int left, int right,int sort[]);

void mergeSort(int tosort[],int n)
{
	int sort[max];

	_mergeSort(tosort,0,n-1,sort);
}

static void _mergeSort(int tosort[],int left,int right,int sort[])
{
	if(left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	
	_mergeSort(tosort,left,mid,sort);
	_mergeSort(tosort,mid+1,right,sort);
	
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int i = begin1;

	while(begin1 <= end1 && begin2 <= end2)
	{
		if(tosort[begin1]<tosort[begin2])
		{
			*(sort+i)=*(tosort+begin1);
			begin1++;
		}
		else
		{
			*(sort+i)=*(tosort+begin2);
			begin2++;
		}
		i++;
	}

	while(begin1<=end1)
	{
		*(sort+i)=*(tosort+begin1);
		begin1++;
		i++;
	}

	while(begin2<=end2)
	{
		*(sort+i)=*(tosort+begin2);
		begin2++;
		i++;
	}

	memcpy(tosort+left,sort+left,(right-left+1)*sizeof(int));
}
