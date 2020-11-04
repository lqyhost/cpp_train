#include <iostream>
#include <vector>
#include <memory>

using namespace::std;

auto myfunc()
{
    return unique_ptr<string>(new string("test"));//临时对象，为右值
}

int main()
{
    //unique_ptr 独占式智能指针,unique_ptr被销毁的时候，指向的对象也被销毁
    unique_ptr<int> upi(new int(100));
    cout<<*upi<<endl;
    //make_unique C++14标准，不支持指定删除器，如果不用删除器，建议优先使用，可以获取更佳的性能表现
    unique_ptr<int> upi1 = make_unique<int>(1000);
    auto upi2 = make_unique<int>(1000);
    //常用操作
    //不支持指针copy
    //unique_ptr<int> upi3(upi1);//错误
    //unique_ptr<int> upi4 = upi1;//错误
    unique_ptr<int> upi5 = move(upi1);//支持，移动以后upi1指向空，upi5指向原来地址，没有释放
    //release() 放弃控制权。返回裸露指针，智能指针指向空，裸指针需要手工delete
    unique_ptr<int> upi6 = make_unique<int>(1000);
    int *pi = upi6.release();//upi6 = nullptr
    delete pi;
    //reset()
    unique_ptr<int> upi7 = make_unique<int>(1000);
    upi7.reset();//置空智能指针并释放智能指针所指向的内存空间
    unique_ptr<int> upi8 = make_unique<int>(1000);
    unique_ptr<int> upi9 = make_unique<int>(1000);
    upi8.reset(upi9.release());//带参数reset，释放upi8所指向的内存空间，并让upi8指向upi9所指向的内存，upi9置空
    // = nullptr 释放智能指针所指向的对象，并将智能指针置空
    unique_ptr<int> upi10 = make_unique<int>(1000);
    upi10 = nullptr;

    //指向数组,数组有自己的析构方式，在类型中一定要加上中括号才能正常的释放，不过同样的需求一般使用vector等模版
    unique_ptr<int[]> upa(new int[10]);

    //get()返回裸指针,但是不要对返回裸指针使用delete
    unique_ptr<int> upi11(new int(1000));
    cout<<*(upi11.get())<<endl;
    //*解引用，获取智能指针指向的对象，可以直接操作
    cout<<*upi11<<endl;
    //swap 交换两个智能指针所指向的对象
    unique_ptr<int> upi13(new int(1001));
    unique_ptr<int> upi14(new int(1002));
    swap(upi13, upi14);
    upi14.swap(upi13);

    //智能指针名字作为判断条件
    unique_ptr<int> upi15(new int(1015));
    if(upi15)//upi15指向某个值，则为true
    {
        cout<<*upi15<<endl;
    }

    //转换为shared_ptr，如果unique_ptr为右值，则可以赋值给shared_ptr
    shared_ptr<string> pss1 = myfunc();
    unique_ptr<int> upi16(new int(1015));
    shared_ptr<int> spi1 = move(upi16);//move 左边值转右值，执行后upi16空，spi1指向原地址
}