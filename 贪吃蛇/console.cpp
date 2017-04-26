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

void Console::putElement(const COORD& pos, char element)const
{
	std::lock_guard<std::mutex> guard{ cusorMutex };
	COORD orgPos = getConsoleCursorPos();
	setConsoleCorsorPos(pos);
	cout.put(element);
	setConsoleCorsorPos(orgPos);
}

void Console::eraseElement(const COORD& pos)const
{
	putElement(pos, ' ');
}

void Console::hideCursor() const
{
	CONSOLE_CURSOR_INFO hideCursorInfo{ 1,false };
	SetConsoleCursorInfo(getConsoleHandle(), &hideCursorInfo);
}

void Console::showCursor() const
{
	CONSOLE_CURSOR_INFO showCursorInfo{ 1,true };
	SetConsoleCursorInfo(getConsoleHandle(), &showCursorInfo);
}

HANDLE Console::getConsoleHandle()const
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	return handle;
}

void Console::setConsoleCorsorPos(const COORD& pos)const
{
	SetConsoleCursorPosition(getConsoleHandle(), pos);
}

COORD Console::getConsoleCursorPos()const
{
	static CONSOLE_SCREEN_BUFFER_INFO csbf;
	GetConsoleScreenBufferInfo(getConsoleHandle(), &csbf);
	return csbf.dwCursorPosition;
}

