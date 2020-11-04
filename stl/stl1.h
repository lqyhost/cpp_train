#include <iostream>
#include <string>
#include <array>

//C++标准库C++ standard library 只要安装了C++编译器就可以用
//标准模版库 standard template library 包含在C++标准库，C++标准库的核心，是用范型编程的编码方式便携的一套库
//要了解 栈（先进后出） 队列（先进先出） 链表（有next指针）

//hash表是在一定空间中，通过hash映射到地址，查找比较快，当元素数量大于hash地址时，hash地址会倍增，然后产生新序列

using namespace std;

namespace _nmsp1
{
    //array 大小是固定的,内存空间是连续的
    void func()
    {
        array<string, 5> mystring = {"sdf","ss","dff","dfw","sdf"};
        cout<<"array size"<<mystring.size()<<endl;
        mystring[0] = "sdfadsfff long  long long long";
        mystring[4] = "sdddd";
        cout<<"sizeof string"<<sizeof(string)<<endl;
        for (size_t i = 0;i<mystring.size();i++)
        {
            const char *sp = mystring[i].c_str();
            cout<<"start"<<endl;
            cout<<"数组元素值 = "<<sp<<endl;
            printf("对象元素地址 =%p\n", &mystring[i]);
            printf("指向的字符串的地址 =%p\n",sp);
            cout<<"end"<<endl;
            //string可以存下的时候直接存在string地址中，如果不能存下则指向外部存储地址
        }
    }
}

namespace _nmsp2
{
    //vector
    //往后面加元素和删除元素很快
    //往中间插入元素可能导致后续元素都要执行重新构造和析构函
    class A
    {
    public:
        int m_i;
        A(){};
        A(int tmp_i):m_i(tmp_i)
        {
            cout<<"构造函数执行"<<endl;
        }
        A(const A& tmp_a)
        {
            m_i = tmp_a.m_i;
            cout<<"拷贝构造函数执行"<<endl;
        }
        ~A()
        {
            cout<<"A 的析构函数执行"<<endl;
        }
    };

    void func()
    {
        vector<A> my_vec;
        for(int i = 0; i<10; i++)
        {
            cout<<"push a:"<<i<<endl;
            my_vec.push(A(i));
        }
    }
}