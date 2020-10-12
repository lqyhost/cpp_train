#include <iostream>
#include <vector>

using namespace::std;

namespace t_space
{
    //可边参数模版variadic template C++11
    //模版调用时候，优先调用符合条件的特化或者偏特化版本，由于可变参模版的特点，如果有特化版本的化，基本是都会调用特化版本
    template <typename...T>
    void func(T... args)
    {
        cout<<sizeof...(args)<<endl;
    }
    template <typename U, typename...T>
    void func(U u, T... args)
    {
        cout<<u<<endl;
        cout<<sizeof...(args)<<endl;
    }

    void func_a()
    {
        cout<<"end"<<endl;
    }
    //由于参数多，一般采用的都是递归的方法对参数进行展开
    template <typename U, typename...T>
    void func_a(const U& u, const T&... args)
    {
        cout<<"get number:"<<u<<endl;
        cout<<sizeof...(args)<<endl;//固定语法sizeof...(args)
        cout<<sizeof...(T)<<endl;//固定语法sizeof...(T)
        func_a(args...);
    }
}
//可变参数类模版
//通过递归集成方法展开参数包
template<typename...A> class my_class{}; //主模版，必须得加这一句，不然下面类模版偏特化会报错
template<typename F, typename... O>
class my_class<F, O...>:private my_class<O...>//偏特化
{
    public:
        my_class():m_i(0)
        {
            cout<<"build"<<this<<endl;
        }
        F m_i;
        void out_put()
        {
            cout<<"m_i"<<m_i<<endl;
        }
};

template<>
class my_class<>
{
    public:
        my_class()
        {
            cout<<"father build"<<endl;
        }
};

int main()
{
    t_space::func(1,2,3,5);
    t_space::func("test",2,3,5);
    cout<<"func_a"<<endl;
    t_space::func_a("test",2,3,5);

    my_class<int,float,double> mc;
    mc.out_put();
    return 0;
}
