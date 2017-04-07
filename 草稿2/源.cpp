#define _CRT_SECURE_NO_WARNINGS
  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void SpictString03(char *scrBuf, char s, char **resltBuf, int *acount)
{
	int tempcount = 0;
	char *p = NULL, *ptem = NULL;
	if (scrBuf == NULL)
	{
		return;
	}
	ptem = p = scrBuf;
	do
	{
		p = strchr(p, s);
		if (p != NULL)
		{
			if (p - ptem>0)
			{
				strncpy(resltBuf[tempcount], ptem, p - ptem);
				resltBuf[tempcount][p - ptem] = '\0';
				tempcount++;
				ptem = p = p + 1;
			}
		}
		else break;

	} while (*p != '\0');
	*acount = tempcount;


}

void getspace(char ***temp)
{
	int i; 
	(*temp) = (char**)malloc(sizeof(char*) * 10);
	for (i = 0; i<10; i++)
	{
		(*temp)[i] = (char*)malloc(sizeof(char) * 30);
	}
}

void freeit(char **resultString, int m)
{
	int i;
	if (resultString == NULL)
	{
		return;
	}
	for (i = 0; i<m; i++)
	{
		free(resultString[i]);
	}
	if (resultString == NULL)
	{
		return;
	}
	free(resultString);

}

void Printit03(char **resultString, int n)
{
	int i;
	for (i = 0; i<n; i++)
	{
		printf("%s\n", resultString[i]);
	}
	printf("count:%d", n);
}
void main()
{
	int count, i;
	char *scrString = "asdasdasd,asdasdasdas,dasdasd,asdasdasda,";
	char ch = ',';
	char **resultString = NULL;
	getspace(&resultString);

	/*resultString=(char**)malloc(sizeof(char*)*10);
	for (i=0;i<10;i++)
	{
	resultString[i]=(char*)malloc(sizeof(char)*100);
	}	*/
	SpictString03(scrString, ch, resultString, &count);

	Printit03(resultString, count);
	freeit(resultString, count);


	printf("\nhello!!\n");
	system("pause");

}
