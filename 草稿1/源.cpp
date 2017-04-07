////#pragma comment(lib,"debug.lib")
//#include<iostream>
//#include<algorithm>
//#include<string>
//#include<vector>
//#include<Windows.h>
//
//
//int main()
//{ 
//	//HINSTANCE his = LoadLibraryA("²Ý¸å.dll");
//	//typedef void(*pShow)();
//	//pShow show = (pShow)GetProcAddress(his, "say");
//	//show(); 
//	//system("pause");
//}
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
int main()
{
	int mod = 1000000007;
	int pow = 1000000000;
	long long answer = 1;
	long long base = 2;
	for (long long i = 1; i <= pow; i <<= 1)
	{
		if (i&pow)
		{
			answer = answer *base % mod;
		}
		base = base*base%mod;
	}
	printf("%lld", answer);
	return 0;
}