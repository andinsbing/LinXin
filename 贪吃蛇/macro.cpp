#include<iostream>
#include "macro.h"

void macroTracingLog(bool on, const char* info)
{
	if (on)
	{
		std::cout << info << std::endl;
	}
}
