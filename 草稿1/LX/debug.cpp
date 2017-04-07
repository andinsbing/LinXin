#include "debug.h"
std::ofstream LX::Debug::outFileStream;
const  LX::StdIOStringBuffer LX::Debug::stdCinBuffer = std::cin.rdbuf();
const  LX::StdIOStringBuffer LX::Debug::stdCoutBuffer = std::cout.rdbuf();
std::ofstream LX::Debug::outputStringBufferTemp;
std::ifstream LX::Debug::inputStringBufferTemp;
bool LX::Debug::isActicve = true;

void LX::Debug::logText(const string & text, const std::ios::openmode & policy, const string & fileAddress)
{  
	if (!isActicve)
	{
		return;
	}
	std::ofstream outFileStream(fileAddress, policy);
	if (!outFileStream.is_open())
	{
		cout << "failed in opening " << fileAddress << '\n';
	}
	else
	{
		outFileStream << text << std::endl;
	}
	outFileStream.close();  
}

void LX::Debug::resetInputBuffer(const string & fileAddress, const std::ios::openmode & policy)
{ 
	if (inputStringBufferTemp.is_open())
	{
		inputStringBufferTemp.close();
	}
	inputStringBufferTemp.open(fileAddress, policy);
	if (!inputStringBufferTemp.is_open())
	{
		cout << "failed in opening " << fileAddress << '\n';
		resetInputBuffer();
		return;
	}
	cin.rdbuf(inputStringBufferTemp.rdbuf());
}

void LX::Debug::resetInputBuffer()
{ 
	cin.rdbuf(stdCinBuffer);
	inputStringBufferTemp.close();
}

void LX::Debug::resetOutputBuffer(const string & fileAddress, const std::ios::openmode & policy)
{ 
	if (outputStringBufferTemp.is_open())
	{
		outputStringBufferTemp.close();
	}
	outputStringBufferTemp.open(fileAddress, policy);
	if (!outputStringBufferTemp.is_open())
	{
		cout << "failed in opening " << fileAddress << '\n';
		resetOutputBuffer();
		return;
	}
	cout.rdbuf(outputStringBufferTemp.rdbuf());
}

void LX::Debug::resetOutputBuffer()
{ 
	cout.rdbuf(stdCoutBuffer);
	outputStringBufferTemp.close();
}

void LX::Debug::turnOnLog()
{
	isActicve = true;
}

void LX::Debug::trunOffLog()
{
	isActicve = false;
}
