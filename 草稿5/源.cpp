#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string> 
#include <algorithm>  
#include <vector>
#include <stack>		
#include<iomanip>
#include<list>	
#include<queue>
#include<set>
#include<map>
#include<numeric>
#include<cmath> 
#include<iterator>
#include<cstdio>
#include<cstring>
#include<math.h> 


using std::endl;
using std::cin;
using std::cout;

const int MAX = (int)5e4;
const int MOD = (int)1e9 + 7;
typedef long long LL;

int getSignedInt()
{
	char ch = getchar();
	while (ch==' ' || ch == '\n'|| ch == '	')
	{
		ch = getchar();
	}
	int ans = 0;
	bool sign = false; 
	if (ch == '-')
	{
		sign = true;
	}
	else
	{
		ans = ch - '0';
	}
	ch = getchar();
	while ('0' <= ch && '9' >= ch)
	{
		ans = ans * 10 + ch - '0';
		ch = getchar();
	}
	return sign ? -ans : ans;
}

int getUnsignedInt()
{
	char ch = 0;
	while ('0'>ch || '9'<ch)
	{
		ch = getchar();
	}
	int ans = 0;
	while ('0' <= ch && '9' >= ch)
	{
		ans = ans * 10 + ch - '0';
		ch = getchar();
	}
	return ans;
}

//LL dp[321][MAX + 2]{};
int prime[(int)1e6];
int primeSize=0; 

int main()
{
	//FILE* pFile;
	//freopen_s(&pFile, "out.txt", "w", stdout);
	//for (int i = 0; i < MAX; i++)
	//{
	//	dp[0][i] = 1;
	//} 
	int temp[6]; 
	for (int i = 0; i < 6; i++)
	{
		temp[i] = getUnsignedInt();
	}
	for (int i = 0; i < 6; i++)
	{
		std::cout << temp[i] << endl;
	}
	system("pause");
	return 0;
}