#pragma once
#include<mutex> 
#include<Windows.h>

class Console
{
	static std::mutex cusorMutex;
public:
	Console();
	~Console();
	//在指定位置输出元素，线程安全
	void putElement(const COORD& pos, char element)const; 
	//清除指定位置的元素，线程安全
	void eraseElement(const COORD& pos)const; 
	void hideCursor()const;
	void showCursor()const;
private:
	void setConsoleCorsorPos(const COORD& pos)const; 
	HANDLE getConsoleHandle()const; 
	COORD getConsoleCursorPos()const;
};

