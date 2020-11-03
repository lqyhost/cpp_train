/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-22 16:47:23
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-24 11:43:13
 * @FilePath: /cpp_train/new/new1.cpp
 */
#include <iostream>

using namespace std;

namespace _np1
{
    class A
    {
    public:
        int i;
        A()
        {}
        virtual void func_a(){}
    };
    void func_1()
    {
        //new 加括号和没有括号的区别
        //当类有构造函数的时候，两个结果一样
        //如果有纯虚函数，两个结果一样
        //new调用中会调用malloc()分配内存
        A *pa0 = new A();//会把一部分成员变量内存清0
        A *pa1 = new A;//不会将成员变量清0
        delete pa0;
        delete pa1;
        //delete调用中会调用free()释放内存
    }

}
//内存池
//减少内存浪费，malloc调用是需要内存空间的
//减少malloc调用次数，会快一点点
//方式：使用malloc申请一大快内存，然后一点一点分配给用户，当这些内存空间不够的时候，再申请一大块
//针对一个类实现一个内存池（方式，通过重载new和delete的方式实现）
class A
{
public:
    static void *operator new(size_t size);
    static void operator delete(void *phead);
    static int m_count;//分配计数统计，new一次统计一次
    static int m_mallo_ccount;//malloc一次统计一次
private:
    A *next;
    static A* m_freeepos;//总是只想一块可以分配出去的内存的首地址
    static int m_trunk_count;
};

int A::m_count = 0;
int A::m_mallo_ccount = 0;

A *A::m_freeepos = nullptr;
int A::m_trunk_count = 50;//一次分配5倍的该内存的大小

void *A::operator new(size_t size)
{
    A *tmp_link;
    if (m_freeepos == nullptr)
    {
        size_t realsize = m_trunk_count*size;
        m_freeepos = reinterpret_cast<A*>(new char[realsize]);//这里的new是全局new，所以这里分配了realsize个字节
        //把分配的5快地址链起来
        tmp_link = m_freeepos;//将tmp_link指针指向m_freeepos分配出来的地址块的首地址
        for(;tmp_link != &m_freeepos[m_trunk_count-1]; ++tmp_link)
        {
            tmp_link->next = tmp_link + 1;
        }
        tmp_link->next = nullptr;
        ++ m_mallo_ccount;
    }
    tmp_link = m_freeepos;
    m_freeepos = m_freeepos->next;
    ++ m_count;
    return tmp_link;
}

void A::operator delete(void *phead)
{
    (static_cast<A*>(phead))->next = m_freeepos;
    m_freeepos = static_cast<A*>(phead);
}

int main()
{
    cout<<"start"<<endl;
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 5000000; i++)
    {
        A *pa = new A();
    }
    end = clock();
    cout<<"time m_count"<<A::m_count<<"m_mallo_ccount: "<<A::m_mallo_ccount<<"time: "<<end-start<<endl;
    return 0;
}