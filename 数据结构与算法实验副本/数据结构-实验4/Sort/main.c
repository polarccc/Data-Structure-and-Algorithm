#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "sort.h"

void generatedata();
void readdata(int data[],int *n);

int main()
{
	FILE *fp_sel = fopen("sel.txt","w+");
        FILE *fp_ins = fopen("ins.txt","w+");
        FILE *fp_mer = fopen("mer.txt","w+");
        FILE *fp_par = fopen("par.txt","w+");

	srand((unsigned)time(NULL));
	int n,data[max],tosort[max];
	int i=0;
	while(i<50){

	generatedata();
	readdata(data,&n);	

	memcpy(tosort,data,sizeof(data));
	//output(data,n,"before");

	size_t t1,t2;

	//output(tosort,n,"before");
	t1 = clock();
	selectSort(tosort,n);
	t2 = clock();
	//output(tosort,n,"after selectsort");
	printf("selectsort:runs in %f seconds for %d objects\n",(t2-t1)/((double)CLOCKS_PER_SEC),n);
	fprintf(fp_sel,"%d %f\n",n,(t2-t1)/((double)CLOCKS_PER_SEC));
	memcpy(tosort,data,sizeof(data));

	//output(tosort,n,"before");
	t1 = clock();
        insertSort(tosort,n);
        t2 = clock();
        //output(tosort,n,"after insertsort");
        printf("insertsort:Runs in %f seconds for %d objects\n",(t2-t1)/((double)CLOCKS_PER_SEC),n);
        fprintf(fp_ins,"%d %f\n",n,(t2-t1)/((double)CLOCKS_PER_SEC));
	memcpy(tosort,data,sizeof(data));

	//output(tosort,n,"before");
	t1 = clock();
        mergeSort(tosort,n);
        t2 = clock();
        //output(tosort,n,"after mergesort");
        printf("mergesort:Runs in %f seconds for %d objects\n",(t2-t1)/((double)CLOCKS_PER_SEC),n);
        fprintf(fp_mer,"%d %f\n",n,(t2-t1)/((double)CLOCKS_PER_SEC));
	memcpy(tosort,data,sizeof(data));

	//output(tosort,n,"before");
	t1 = clock();
        partationSort(tosort,0,n-1);
        t2 = clock();
        //output(tosort,n,"after partationsort");
        printf("partationsort:Runs in %f seconds for %d objects\n",(t2-t1)/((double)CLOCKS_PER_SEC),n);
	fprintf(fp_par,"%d %f\n",n,(t2-t1)/((double)CLOCKS_PER_SEC));
	i++;
	}
	fclose(fp_sel);
	fclose(fp_ins);
	fclose(fp_mer);
	fclose(fp_par);
	return 0;
}

void generatedata()
{
	FILE *fp = fopen("num.txt","w+");
       	fseek(fp,0,SEEK_SET);
	int n=rand()%100001;
	fprintf(fp,"%d\n",n);
	for(int i=0;i<n;i++)
	{
		fprintf(fp,"%d ",rand()%100001);
	}
	fclose(fp);
}

void readdata(int data[],int *n)
{
	FILE *fp = fopen("num.txt","r");
	fseek(fp,0,SEEK_SET);
	fscanf(fp,"%d",n);
	for(int i=0;i<*n;i++)
	{
		fscanf(fp,"%d",data+i);
	}
	fclose(fp);
}

void output(int data[],int n, char *info)
{
	printf("%s\n",info);
	for(int i=0;i<n;i++)
	{
		printf("%d ",data[i]);
	}
	printf("\n");
}
