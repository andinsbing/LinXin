//#include<iostream> //直接把头文件的内容拷贝过来
//
//using namespace std; //表示下面的内容可以直接使用 
//std命名空间的东西,xxxxx ,如果不加的话，用std里面的东西，就必须写成std::xxxxxx
// 
//
//int main()//c++ 里面,main是开始的函数，规定它的返回值是int,返回值是给操作系统用的，
//		//返回0的代表程序正常退出，返回非0的数，代表的是程序意外退出
//		//main 两种写法，一种是 main(),另一种是 main(int argc,char* argv[])
//{
//	int x, y, sum; //类型  + 变量名 ,定义一个变量
//	cout << "Please input two interger:" << '\n';
//	cin >> x >> y;
//	sum = x + y;
//	cout << sum;
//	return 0;  
//}

#include<iostream>

class Complex//类的声明方式  class + 类型的名称 {};
{ 
	double real; //class 里面，三种访问权限的修饰符，pulic ,private,protected
				//没有说明的情况下，double real 和 private double real等价的 
	double imag;
	double *p;
	void inil(double r, double i)//函数没有说明访问权限，也是private的
	{
		real = r; 
		imag = i;
	} 
	//没有写任何的构造函数，仍可以创建对象，是因为 编译器会自动添加构造函数
	//添加的构造函数有
	// 不带参数的构造函数  Complex(){}
	// 添加一个拷贝构造函数 Complex(const Complex&){};
	//如果不写析构函数 ~Complex(){}
	//编译器会自动给你添加一个析构函数
	// 也就是添加一个 ~Complex(){}

	//用代码模拟一下若果构造函数和析构函数都不写，编译器大概会填写的代码
	Complex()
	{
		p = new double[66];
	}; //构造一个对象
	Complex(const Complex& target)//通过自己类的一个对象来构造一个新的对象
	{
		this->imag = target.imag;
		this->real = target.real;
	}
	 
	~Complex()//释放自己这个对象所占用的资源
	{ 
		delete p;
	} 
};

class Object
{
public:
	Object()
	{
		std::cout << "构造函数调用\m";
	}
	~Object()
	{
		std::cout << "析构函数调用\n";
	}
};
 

class str
{
	Object* p;
public:
	str()
	{ 
		p = new Object();
	}
	void realse()
	{
		delete p;//虽然这种方法也可以，但是你调用这个函数之后，就不能再使用p;
	}
	~str()
	{ 
		//如果不在析构函数里面释放掉p指向的Object对象占用的内存，以后就没有机会释放Object占用的内存，
		//在整个程序结束之前，Object对象都会一直存在。
		delete p;//释放Objext占用的内存 释放 new得来的空间 
	}
};

int add(int x, int y)//函数重载就是 函数名字一样，参数不一样
{
	return x + y;
}
double add(double x, double y)
{
	return x + y;
}


//直接类型+名称构造对象
//函数结束时，会调用析构函数，释放资源
//obj内存在栈中，栈中内存系统会自动回收
void fun()
{
	Object obj;
}

//通过 new运算得来的对象
//函数结束时不会释放资源
//new 得来的对象，如果要释放，就必须用delete手动释放
//obj对象在堆中，堆中的内存，必须由程序员手动显示回收
void fun2()
{
	Object* obj = new Object();
	delete obj;
}


class Widget
{
private:
	int width;
	int hight;
	const int size;
public:
	//类里面还有一个用来构造对象的东西，叫初始化列表
	//创建一个类，会先用初始化列表来给类里面的数据初始化，
	//然后才会调用构造函数
	Widget():width(0),hight(1),size(10)  //效果可以等于 width =0,hight =1
	{  
		std::cout << "构造函数调用\n";
	}
	~Widget()
	{
		std::cout << "析构函数调用\n";
	}
};



class Show
{
public:
	Show& operator<<(int x)
	{
		std::cout << "调用 运算符重载函数";
			std::cout << x << '\n';
		return *this;
	}
};



int main()
{		 
	//cout << "666";//当前命名空间找不到cout,因为cout是在std命名空间里面的
	//using namespace std;//变量或函数如果找不到，就在std空间里面找
	//cout << "666";
	////::cout找不到,但是std::cout可以找到，所以不会报错
	//std 是 c++标准库所以函数和类和数据的命名空间
	//int x1, x2, x3, x4, x5, x6;
	//x1 >> 1;
	//std::cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6;
	//std::cin 中 >> 原始的是位运算的>>右移符号
	//cin 是一个对象，cin对象对应类里面，对运算符>>进行了重载
	//本质上
	//std::cin >> x1;
	//std::cin.operator >> (x1);
	//函数返回的 cin 本身
	
	Show show; 
	show << 1 << 2 << 3 << 4 << 5;
	system("pause");
	return 0;
}