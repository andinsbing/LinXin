#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define Size(a)		(sizeof(a)/sizeof(*a))

int i = 0, j = 0;//循环变量

				 //把第一种、2copy到3中并排序
char **getmem(int num)//分配内存
{
	char **p2 = NULL;
	p2 = (char**)malloc(sizeof(char*)*num);
	if (p2 == NULL)
	{
		return;
	}
	for (i = 0; i<num; i++)
	{
		p2[i] = (char*)malloc(sizeof(char) * 100);
		//sprintf(p2[i],"%d",i+1);
	}
	return p2;
}
void Print(char **p, int n)		 //打印
{
	if (p == NULL)
	{
		return;
	}
	for (i = 0; i<n; i++)
	{
		printf("%s\n", p[i]);
	}
	printf("\n");
}
void sortSt(char **array, int num)  //排序
{
	char *temp = NULL;

	for (i = 0; i<num; i++)
	{
		for (j = i; j<num; j++)
		{
			if (strcmp(array[i], array[j])>0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}
char **sort(char **p1, int num1, char(*p2)[30], int num2, int *num3)
{
	int num = num1 + num2;
	char **p = p1;
	char **q = p2;
	char **result;
	if (p == NULL || q == NULL)
	{
		return;
	}
	result = getmem(num);
	for (i = 0; i<num1; i++)
	{
		result[i] = p[i];
	}
	for (i = 0; i<num2; i++)
	{
		result[i + num1] = q[i];
	}
	sortSt(result, num);
	*num3 = num;
	return result;


}


void sort02(char **p1, int num1, char(*p2)[30], int num2, int *num3, char **re)
{
	int num = num1 + num2;
	char **p = p1;
	char **q = p2;
	char **result = re;
	if (p == NULL || q == NULL)
	{
		return;
	}
	for (i = 0; i<num1; i++)
	{
		result[i] = p[i];
	}
	for (i = 0; i<num2; i++)
	{
		result[i + num1] = q[i];
	}
	sortSt(result, num);
	*num3 = num;
	//return result;


}


void Free(char ***p, int n)
{
	char **tmp = NULL;
	if (p == NULL)
	{
		return;
	}
	tmp = *p;
	for (i = 0; i < n; i++)
	{
		if (p[i] != NULL)
		{
			free(tmp[i]);
			tmp[i] = NULL;
		}
	}
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}

}

char* newStr(char*p)
{
	int len = strlen(p);
	char* str = malloc(len * sizeof(char) + 1);
	for (int i = 0; i < len; i++)
	{
		str[i] = p[i];
	}
	str[len] = 0;
	return str;
}

void main()
{
	int num, num2 = 0;
	char *p1[] = { "222222","111111111","3333333" };
	char *p2[4][30] = { "bbbbbb","aaaaa","zzzzzzzzz","ccccccccc" };
	char **p3 = NULL;
	//char ***myerrp3	 =  NULL;
	num = (Size(p1) + Size(p2));
	p3 = getmem(num);
	//myerrp3 = getmem(num);
	Print(p1, Size(p1));
	Print(p2, Size(p2));
	p3 = sort(p1, Size(p1), p2, Size(p2), &num2);
	//sort02(p1, Size(p1), p2, Size(p2), &num2,p3);
	printf("after!\n");
	Print(p3, num);
	Free(&p3, num);

	printf("num2 :%d\n", num2);

	//Free(myerrp3,num);
	printf("\n");
	system("pause");

}