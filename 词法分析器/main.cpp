#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<map> 
#include<cctype>
#include<unordered_set>
#include<vector>

using std::cin;
using std::cout;
using std::endl;

/*
digit  [0-9]+{.}*{0-9}**
id     [a-zA-Z_][a-zA-Z_0-9]*
op     [.,|%^~£¡+-*=/==]
final  ;
exp    [digit|id|op exp| exp op| exp op exp] final

*/

class Token
{
public:
	enum Type
	{
		KEYWORDS,
		OP,
		SEPARATOR,
		CONSTANT,
		ID
	};
public:
	Token(const std::string& sybol, Type type) :
		symbol(symbol),
		type(type)
	{

	}
	const std::string symbol;
	const Type type;
};

class ID:public Token
{ 
}; 


class OpBase:public Token
{ 
}; 


std::unordered_set<std::string> keywords
{
	{
		"char",
		"int",
		"true",
		"false",
		"for",
		"if",
		"else",
		"return",
		"break",
		"continue",
		"do",
		"while",
		"inline",
		"eunm"
	} 
};
std::unordered_set<std::string> op
{
	{
		"+",
		"-",
		"*",
		"/",
		"%",
		"++",
		"--",
		"!",
		"=",
		"==",
		"!=",
		"|",
		"||",
		"&",
		"&&",
		"^",
		"new",
		"delete"
	}
};
std::unordered_set<std::string> separator
{
	{
		";",
		",",
		"{",
		"}",
		"(",
		")"
	}
};

class Scanner
{
public:  
	void scan(const std::string& source, const std::string& outFileRoot)
	{ 
		openFile(source, outFileRoot);
		if (!isFileStreamAviliable())
		{
			closeFileStream(); 
			cout << "can not open file\n" << endl;
			return;
		} 
		char ch = peek();
		while (ch != EOF)
		{
			if (std::isspace(ch))
			{
				drop();
			}
			else if (std::isalpha(ch) || ch == '_')
			{
				std::string temp;
				while (std::isalnum(ch) || ch == '_')
				{
					temp.push_back(ch);
					drop();
					ch = peek();
				}
				tokens.push_back(std::move(temp));
			}
			else if (std::ispunct(ch))
			{
				drop();
				tokens.push_back({ ch });
			}
			else if (std::isdigit(ch))
			{
				std::string temp;
				while (std::isdigit(ch))
				{
					temp.push_back(ch);
					drop();
					ch = peek();
				}
				tokens.push_back(std::move(temp));
			}
			else
			{
				cout << "can not match   " << (int)ch << ":  " << ch << endl;
			}
			ch = peek();
		}
		for (auto& i : tokens)
		{
			outf << i << '\n';
		}
		closeFileStream();
	}
private: 
	void openFile(const std::string& in, const std::string& out)
	{
		inf.open(in);
		outf.open(out);
	}
	void closeFileStream()
	{
		inf.close();
		outf.close();
	}
	bool isFileStreamAviliable()const
	{
		return inf&&outf;
	}
	char peek()
	{
		return inf.peek();
	} 
	void drop()
	{
		inf.get();
	} 
	std::vector<std::string> tokens;
	std::ifstream inf;
	std::ofstream outf; 
};



int main()
{  
	Scanner scanner;  
	scanner.scan("in.txt", "out.txt"); 
	system("pause");
}