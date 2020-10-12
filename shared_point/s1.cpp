#include <iostream>
#include <vector>
#include <memory>
using namespace::std;

class A
{

};

shared_ptr<int> makes(int i)
{
    return shared_ptr<int>(new int(i));//使用int* 显式创建shared_ptr
}

void shared_ptr_fuc(shared_ptr<int> &p)
{
    cout<<p.use_count() <<endl;
    cout<<"p:"<<*p<<endl;
}

void my_delete(int *p)
{
    cout<<"my_delete: "<<*p<<endl;
    delete p;
}

int main()
{
    //shared_ptr原理是引用计数，每个shared_ptrzhizheng都指向同样的内存
    //用法 shared_ptr<类型> 
    shared_ptr<int> pi; //默认初始化，产生一个int指针，目前指向空
    shared_ptr<int> pi1(new int(100));//赋值初始化
    //shared_ptr<int> pi2 = new int(200);//错误，智能指针是explicit，不可以隐式类型转换
    shared_ptr<int> pi3 = makes(190);//返回值初始化
    shared_ptr<int> pi4 = make_shared<int>(100);//标准库的函数模版，安全而且高效
    auto pi5 = make_shared<int>(190);
    //所有的局部shared_ptr在函数运行结束的地方内存会自动释放，不会有内存泄漏
    auto pi6(pi5);//pi6指向pi5所指向的对象，并且对象指针计数加1

    shared_ptr_fuc(pi6);//智能指针当作实参被传递
    //对象多被一个智能指针指向时，对象指针计数加一，反之减少一
    auto pi7(pi5);//对象指针加一
    pi7 = pi3;//对象指针减一
    //智能指针函数
    //use_count 指向对象指针计数
    //unique 是否独占
    //reset() 不带参数时，如果是唯一指向对象的指针，那么释放指针所指向的对象，并置空，否则不做操作
    //reset(x) 带参数时候，原来对象指针数减一，并指向新的内存
    //* 解引用，获得指针指向的对象
    //get() 返回智能指针中保存的指针(裸指针)，小心使用
    //swap(p1, p2) 交换两个智能指针所指向的对象
    swap(pi5,pi7);
    shared_ptr_fuc(pi7);
    // = nullptr 对象指针计数减1 

    //shared_ptr 指定删除器
    //shared_ptr 默认使用delete作为资源析构方式，如果需要使用自定义析构函数，只需要添加在参数列表中即可
    shared_ptr<int> pi8(new int(298), my_delete);//自定义析构函数
    shared_ptr<int> pi9(new int(299), [](int *p){cout<<"lambda:"<<*p<<endl; delete p;});

    //shared_ptr 数组
    shared_ptr<A> pa1(new A[10], [](A *p){delete []p;});//使用自己的删除器来处理数组问题
    shared_ptr<A> pa2(new A[10], default_delete<A[]>());//也可以用来处理数组,注意写法，要标明是A类型数组
    // shared_ptr<A[]> pa3(new A[10]);//教程说可以这样用，但是调试发现代码不能指向，存疑
    // shared_ptr<int[]> pa4(new int[10]);
    //pa4[0] = 15;
    return 0;
}