//#include<iostream> //ֱ�Ӱ�ͷ�ļ������ݿ�������
//
//using namespace std; //��ʾ��������ݿ���ֱ��ʹ�� 
//std�����ռ�Ķ���,xxxxx ,������ӵĻ�����std����Ķ������ͱ���д��std::xxxxxx
// 
//
//int main()//c++ ����,main�ǿ�ʼ�ĺ������涨���ķ���ֵ��int,����ֵ�Ǹ�����ϵͳ�õģ�
//		//����0�Ĵ�����������˳������ط�0������������ǳ��������˳�
//		//main ����д����һ���� main(),��һ���� main(int argc,char* argv[])
//{
//	int x, y, sum; //����  + ������ ,����һ������
//	cout << "Please input two interger:" << '\n';
//	cin >> x >> y;
//	sum = x + y;
//	cout << sum;
//	return 0;  
//}

#include<iostream>

class Complex//���������ʽ  class + ���͵����� {};
{ 
	double real; //class ���棬���ַ���Ȩ�޵����η���pulic ,private,protected
				//û��˵��������£�double real �� private double real�ȼ۵� 
	double imag;
	double *p;
	void inil(double r, double i)//����û��˵������Ȩ�ޣ�Ҳ��private��
	{
		real = r; 
		imag = i;
	} 
	//û��д�κεĹ��캯�����Կ��Դ�����������Ϊ ���������Զ���ӹ��캯��
	//��ӵĹ��캯����
	// ���������Ĺ��캯��  Complex(){}
	// ���һ���������캯�� Complex(const Complex&){};
	//�����д�������� ~Complex(){}
	//���������Զ��������һ����������
	// Ҳ�������һ�� ~Complex(){}

	//�ô���ģ��һ���������캯����������������д����������Ż���д�Ĵ���
	Complex()
	{
		p = new double[66];
	}; //����һ������
	Complex(const Complex& target)//ͨ���Լ����һ������������һ���µĶ���
	{
		this->imag = target.imag;
		this->real = target.real;
	}
	 
	~Complex()//�ͷ��Լ����������ռ�õ���Դ
	{ 
		delete p;
	} 
};

class Object
{
public:
	Object()
	{
		std::cout << "���캯������\m";
	}
	~Object()
	{
		std::cout << "������������\n";
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
		delete p;//��Ȼ���ַ���Ҳ���ԣ�����������������֮�󣬾Ͳ�����ʹ��p;
	}
	~str()
	{ 
		//��������������������ͷŵ�pָ���Object����ռ�õ��ڴ棬�Ժ��û�л����ͷ�Objectռ�õ��ڴ棬
		//�������������֮ǰ��Object���󶼻�һֱ���ڡ�
		delete p;//�ͷ�Objextռ�õ��ڴ� �ͷ� new�����Ŀռ� 
	}
};

int add(int x, int y)//�������ؾ��� ��������һ����������һ��
{
	return x + y;
}
double add(double x, double y)
{
	return x + y;
}


//ֱ������+���ƹ������
//��������ʱ������������������ͷ���Դ
//obj�ڴ���ջ�У�ջ���ڴ�ϵͳ���Զ�����
void fun()
{
	Object obj;
}

//ͨ�� new��������Ķ���
//��������ʱ�����ͷ���Դ
//new �����Ķ������Ҫ�ͷţ��ͱ�����delete�ֶ��ͷ�
//obj�����ڶ��У����е��ڴ棬�����ɳ���Ա�ֶ���ʾ����
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
	//�����滹��һ�������������Ķ������г�ʼ���б�
	//����һ���࣬�����ó�ʼ���б���������������ݳ�ʼ����
	//Ȼ��Ż���ù��캯��
	Widget():width(0),hight(1),size(10)  //Ч�����Ե��� width =0,hight =1
	{  
		std::cout << "���캯������\n";
	}
	~Widget()
	{
		std::cout << "������������\n";
	}
};



class Show
{
public:
	Show& operator<<(int x)
	{
		std::cout << "���� ��������غ���";
			std::cout << x << '\n';
		return *this;
	}
};



int main()
{		 
	//cout << "666";//��ǰ�����ռ��Ҳ���cout,��Ϊcout����std�����ռ������
	//using namespace std;//������������Ҳ���������std�ռ�������
	//cout << "666";
	////::cout�Ҳ���,����std::cout�����ҵ������Բ��ᱨ��
	//std �� c++��׼�����Ժ�����������ݵ������ռ�
	//int x1, x2, x3, x4, x5, x6;
	//x1 >> 1;
	//std::cin >> x1 >> x2 >> x3 >> x4 >> x5 >> x6;
	//std::cin �� >> ԭʼ����λ�����>>���Ʒ���
	//cin ��һ������cin�����Ӧ�����棬�������>>����������
	//������
	//std::cin >> x1;
	//std::cin.operator >> (x1);
	//�������ص� cin ����
	
	Show show; 
	show << 1 << 2 << 3 << 4 << 5;
	system("pause");
	return 0;
}