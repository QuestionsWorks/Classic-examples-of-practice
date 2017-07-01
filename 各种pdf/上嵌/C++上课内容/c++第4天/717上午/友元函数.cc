#include<iostream>
using namespace std;

class Test
{
	//声明:fun()是Test的友元函数("朋友")
	//友元函数不是成员函数,fun()和Test是平等的
	//不受类中访问修饰符的限制
	friend void fun(Test &t);
	int m_data;
public:
	Test(int data = 123):m_data(data){}
	~Test(){}
};

void fun(Test &t)
{
	cout <<"Test t.m_data = "<<t.m_data<<endl;
	return ;
}

int main(int argc,char **argv)
{
	Test t;
	fun(t);
	return 0;
}
