#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>  
#include<algorithm>  

using std::endl;
using std::cin;
using std::cout;
using std::string;
typedef long long LL;
const int MAX = (int)20;

LL extGcd(LL a, LL b, LL& x, LL& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	LL ans = extGcd(b, a%b, y, x);
	y -= (a / b)*x;
	return ans;
}

LL modInv(LL a, LL mod)
{
	LL x;
	LL y;
	extGcd(a, mod, x, y);
	return (x%mod + mod) % mod;
}

int main()
{ 
	system("pause");
}