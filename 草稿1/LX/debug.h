#pragma once 
#include<string>
#include<iostream> 
#include<fstream>  

namespace LX
{    
	using std::cin;
	using std::cout;
	using std::string;
	typedef decltype(cin.rdbuf()) StdIOStringBuffer;
	class Debug
	{
	public:
		static void logText(const string& text, const std::ios::openmode& policy = std::ios::app, const string& fileAddress = "LX_Debug_Log.txt");
		static void resetInputBuffer(const string& fileAddress, const std::ios::openmode& policy = std::ios::app);
		static void resetInputBuffer();
		static void resetOutputBuffer(const string& fileAddress, const std::ios::openmode& policy = std::ios::app);
		static void resetOutputBuffer();
		static void turnOnLog();
		static void trunOffLog();
	private:
		static std::ofstream outFileStream;
		static const StdIOStringBuffer stdCinBuffer;
		static const StdIOStringBuffer stdCoutBuffer;
		static std::ofstream outputStringBufferTemp;
		static std::ifstream inputStringBufferTemp;
		static bool isActicve;//is able to log text
	};
	  
}
