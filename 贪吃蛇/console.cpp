#include<iostream>
#include "console.h"
using std::cout;

std::mutex Console::cusorMutex;

Console::Console()
{
}

Console::~Console()
{
}

void Console::putElement(const COORD& pos, char element)
{
	std::lock_guard<std::mutex> guard{ cusorMutex };
	COORD orgPos = getConsoleCursorPos();
	setConsoleCorsorPos(pos);
	cout.put(element);
	setConsoleCorsorPos(orgPos);
}

void Console::eraseElement(const COORD& pos)
{
	putElement(pos, ' ');
}

HANDLE Console::getConsoleHandle()
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	return handle;
}

void Console::setConsoleCorsorPos(const COORD& pos)
{
	SetConsoleCursorPosition(getConsoleHandle(), pos);
}

COORD Console::getConsoleCursorPos()
{
	static CONSOLE_SCREEN_BUFFER_INFO csbf;
	GetConsoleScreenBufferInfo(getConsoleHandle(), &csbf);
	return csbf.dwCursorPosition;
}

