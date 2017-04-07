#pragma once

namespace LX
{  
	#include<sstream> 

	template<class T1,class T2>
	struct isSameType
	{
		static const bool ans = false;
	};
	template<class T>
	struct isSameType<T,T>
	{
		static const bool ans = true;
	};

	class TypeConvert
	{
	public: 
		template<class In_Type,class Out_Type>
		static void to(const In_Type& in,Out_Type& out)
		{
			bufferString << in;
			checkState();
			bufferString >> out;
			checkState();
			resetBuffer();
		} 
	private:
		static void checkState()
		{ 
			if (bufferString.fail()) 
			{
				throw std::exception("input/output operation failed in converting");
			}
		}
		static void resetBuffer()
		{
			bufferString.str("");
		}
	private:
		static std::stringstream bufferString;
	}; 
}