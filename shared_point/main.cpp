#include <iostream>
#include <vector>
using namespace::std;


void test_func()
{
    int i;
    i = 5;
    static int j=12;//局部静态对象，编译器会帮忙分配和释放
}

class A
{};

int main()
{
    //new 为动态分配，存储在堆上
    //new基本类型是随机值，new类调用类的默认构造函数
    int *pi0 = new int;//随机值
    int *pi1 = new int(100);
    int *pi2 = new int();//会初始化为0
    string *pstr = new string("test string");
    vector<int> *pvector = new vector<int>{1,3,5,7};
    *pi1 = 15;
    //new  与delete需要成对出现
    //delete 只能调用一次
    delete pi0;delete pi1;delete pi2;delete pstr;delete pvector;
    A a;//编译器帮忙创建和销毁a对象
    int i = 12;
    int *p = &i;
    //delete p; //错误，不是new的内存不能使用delete
    int *pci = new int(300);
    delete pci;
    pci = nullptr;//可以养成在指针释放以后将指针指向空地址的习惯，这样可以避免指针指向错误，导致意外使用数据或删除数据
    //operator new()和operator delete()
    int *pi = new int;//void *operator new(size_t __sz) 在堆上分配指定大小的内存空间，如果是类对象，还会调用类对象的构造函数
    delete pi;//void operator delete(void *__p, size_t __sz) noexcept 释放指定地址的指定大小的内存，如果是类对象还会调用类对象的析构函数
    A *pA =  new A[2]();
    delete []pA;
    //直接new的指针称为裸指针，为了避免裸指针容易出现的内存泄漏，可以使用智能指针
    //auto_ptr(新标准弃用) unique_ptr shared_ptr weak_ptr
    //三种智能指针实际上都是类模版
    //shared_ptr 共享式指针，多个指针同时指向同一个对象，最后一个执政销毁时候，对象会被释放
    //unique_ptr 独占式指针，同一个时间内，只有一个执政能够指向该对象，对象的所有权限是可以转移的

    return 0;
}