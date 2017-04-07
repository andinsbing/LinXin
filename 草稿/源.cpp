#ifdef DLL_TEST_API
#else
#define DLL_TEST_API _declspec(dllexport)
#include<iostream>
extern "C" void  DLL_TEST_API say()
{
	std::cout << "in the dll" << std::endl;
}
int  DLL_TEST_API add(int a, int b)
{
	return a + b;
}

#endif // DLL_TEST_API
