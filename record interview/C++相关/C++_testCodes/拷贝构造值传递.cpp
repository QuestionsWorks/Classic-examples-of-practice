#include <iostream>
using namespace std;

class CExample
{
private:
    int a;
public:
    //构造函数
    CExample(int b)
    {
        a = b;
        cout << "Creat:"<< a << endl;
    }
    //拷贝构造函数
    CExample(const CExample &C)
    {
        a = C.a;
        cout << "copy" << endl;
    }
    ~CExample()
    {
        cout << "delete:" << a << endl;
    }
    // 一般函数
    void show()
    {
        cout << a << endl;
    }
};

// 全局函数，传入的是对象
void g_Fun(CExample C)
{
    cout << "test" << endl;
}

int main()
{
    CExample test(1);
    //传入对象
    g_Fun(test);
    return 0;
}
/*
Creat:1
copy
test
delete:1
delete:1

*/




