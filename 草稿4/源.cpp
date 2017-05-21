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
#include<math.h>
#include<unordered_set>
#include<unordered_map>
using std::endl;
using std::cin;
using std::cout;
using std::string;

const int MAX = (int)1e6 + 5;
const int MOD = (int)1e9 + 7;
typedef long long LL; 
 

std::unordered_multiset<int> hash;

struct
{
	int count;
	long double mid;
	long double absDifference;
	long double sum;
}point{ 0,0,0 ,0 };

inline void insert(int val)
{
	hash.insert(val);
	point.sum += val;
	point.count++;
	point.mid = point.sum / point.count;
	long double sub = point.mid - val;
	long double absSub = (sub >= 0 ? sub : -sub);
	point.absDifference += absSub*point.count;
}

auto it = hash.begin();
inline void del(int val)
{
	it = hash.find(val);
	if (it == hash.end())
	{
		cout << -1 << '\n';
		return;
	}
	hash.erase(it);
	point.count--;
	point.sum -= val; 
	point.mid = point.sum / point.count;
	long double sub = val - point.mid;
	long double absSub = (sub >= 0 ? sub : -sub); 
	point.absDifference -= absSub*point.count;
}

void query()
{
	cout << (long long)(point.absDifference) << '\n';
}

int main()
{
	int numSize;
	int querySize;
	cin >> numSize >> querySize;
	int temp;
	for (int i = 0; i < numSize; i++)
	{
		cin >> temp;
		insert(temp);
	}
	int queryKind;
	int queryNum;
	auto it = hash.begin();
	for (int i = 0; i < querySize; i++)
	{
		cin >> queryKind;
		switch (queryKind)
		{
		case 1:
			cin >> queryNum;
			insert(queryNum);
			break;
		case 2:
			cin >> queryNum;
			del(queryNum);
			break;
		case 3:
			query();
			break;
		}
	}
	system("pause");
}