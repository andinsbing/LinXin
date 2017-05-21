#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<algorithm> 
#include<vector>
#include<stdio.h>
#include<time.h>
using namespace std;
typedef long long LL;

const LL MOD = 1e9 + 7;
const int MAX = (int)1e6;

bool dp[MAX*10]{};

int main()
{ 
	dp[0] = true;
	for (int i = 1; i <= MAX; i++)
	{
		if (!dp[i])
		{
			dp[i * 10] = true;

		}
	}

	return 0;
}