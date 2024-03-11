#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>
typedef struct
{
    char CH;
    int weight;
    int parent, lchild, rchild;
}tree;
typedef struct
{
    char code[30];
    int cnt;
}codetype;

void Read(char *a)
{

    	FILE *fp = fopen("input.txt", "r");
    	if (fp == NULL)
    	{
        	printf("fail to open!\n");
    	}
    	else
    	{
        	fgets(a,200,fp);
       	 	fclose(fp);
    	}
}
void Write(char *b)
{
   FILE *fp = fopen("text3.txt","w");
    if (fp == NULL)
    	{
        	printf("fail to open!\n");
    	}
    	else
    	{
        	fputs(b,fp);
       	 	fclose(fp);
    	}
}

void Createtree(tree *hfmTree, int N, char a[200])//构建哈夫曼树，传数组hfmTree和字符个数N做参数
{
    int i, j, min1, min2;
    int m, c;
    int len;
    len = strlen(a);
    hfmTree[0].CH = ' ';//空格用0号单元直接存
    hfmTree[0].parent = hfmTree[0].lchild = hfmTree[0].rchild = -1;
    for(i=0;i<N;i++)
    {
        hfmTree[i].weight = 0;
    }
    for (i = 1; i<N; i++)
    {
        if(i<=26){
        hfmTree[i].CH = 'A' + i - 1;}
        else if(i == 27)
            hfmTree[i].CH = ',';
        else if(i == 28)
            hfmTree[i].CH = '.';
        hfmTree[i].parent = hfmTree[i].lchild = hfmTree[i].rchild = -1;
    }

    for(i=0;i<len;i++)
    {
        for(j=0;j<N;j++)
        {
            if(a[i] == hfmTree[j].CH)
            {
                hfmTree[j].weight = hfmTree[j].weight+1;
                break;
            }
        }
    }

    //找到的最小值作为新根的左孩子，次小值作为右孩子
    for (i = N; i<2 * N - 1; i++)
    {
        min1 = 99999;//最小值
        min2 = 99999;//次小值
        m = 0; c = 0;
        for (j = 0; j<i; j++)
        {
            if (hfmTree[j].parent == -1)
                if (hfmTree[j].weight<min1)
                {
                    c = m;
                    min2 = min1;
                    min1 = hfmTree[j].weight;
                    m = j;
                }
                else if (hfmTree[j].weight<min2)
                {
                    min2 = hfmTree[j].weight;
                    c = j;
                }

        }
        hfmTree[i].weight = min1 + min2;
        hfmTree[i].CH = ' ';
        hfmTree[i].lchild = m;
        hfmTree[i].rchild = c;
        hfmTree[m].parent = i;
        hfmTree[c].parent = i;
        hfmTree[i].parent = -1;
    }
}
void Hfmcode(tree *hfmTree, codetype *codeFile, int N)//哈夫曼编码
{
    int i, p, c;
    codetype S;
    for (i = 0; i<N; i++)//对N的字符进行编码
    {
        c = i;
        p = hfmTree[c].parent;
        S.cnt = N;
        S.code[N] = '\0';
        while (p != -1)
        {
            if (hfmTree[p].lchild == c)
                S.code[--S.cnt] = '0';
            else
                S.code[--S.cnt] = '1';
            c = p;
            p = hfmTree[c].parent;
        }

        codeFile[i] = S;
    }

}
void Decode(tree *hfmTree,char *B, int N, char b[200])//解码过程
{
    int i,count=0,j=0;

    i = 2*N-2;
    while (b[j]!='\0')
    {
        if (b[j] == '0')
            i = hfmTree[i].lchild;
        else if (b[j] == '1')//
            i = hfmTree[i].rchild;
        if (hfmTree[i].lchild == -1 || hfmTree[i].rchild == -1)
        {
            B[count] = hfmTree[i].CH;
            count++;
            i = 2*N-2;
        }
        j++;
    }
    B[count] = '\0';

}
int main()
{
    int N;
    int i, j;
    char a[200];
    char b[200];
    char *B,c;
    FILE *fp1,*fp2;
    tree *hfmTree;
    codetype *codeFile;
    printf("The number of character sets:");
    scanf("%d", &N);
    B = (char *)malloc(sizeof(char) * 40);
    codeFile = (codetype *)malloc(sizeof(codetype)*N);
    hfmTree = (tree *)malloc(sizeof(tree)*(2 * N - 1));
    fp1 = fopen("text2.txt","w");
    fp2 = fopen("text4.txt","w");
    if(fp1 == NULL)
        return 0;
    if(fp2 == NULL)
        return 0;
    Read(a);
    printf("the text is:%s\n",a);
    Createtree(hfmTree, N, a);//建树
    Hfmcode(hfmTree, codeFile, N);//编码
    for (i = 0; i<N; i++)
    {
        if(hfmTree[i].weight != 0){
        printf("The encoding of %c:", hfmTree[i].CH);
        printf("%s", codeFile[i].code + codeFile[i].cnt);
        printf("\n");
        }
    }
    printf("The text encoding will be stored in text2.txt\n");
    for (i = 0; i < strlen(a); i++)
    {
        if (a[i] == ' ')
            fprintf(fp1,"%s", codeFile[0].code + codeFile[0].cnt);
        else if (a[i] == ',')
            fprintf(fp1,"%s", codeFile[27].code + codeFile[27].cnt);
        else if (a[i] == '.')
            fprintf(fp1,"%s", codeFile[28].code + codeFile[28].cnt);
        else
            fprintf(fp1,"%s", codeFile[a[i] - 'A' + 1].code + codeFile[a[i] - 'A' + 1].cnt);//由于是倒着存的所以正着输出时要找到起始点
    }
    fclose(fp1);
    printf("\n\n");
    printf("The encoding of this English text is the input encoding that requires translation :\n");
    scanf("%s",&b);
    Write(b);

    Decode(hfmTree, B, N, b);
    printf("\n");
    printf("The code translation will be stored in text4.txt:\n");
    fprintf(fp2,"%s", B);
    return 0;
}
