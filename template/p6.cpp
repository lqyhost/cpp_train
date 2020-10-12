#include <iostream>
#include <vector>

using namespace::std;


//类模版的成员函数模版
template <typename T, typename U>
class B
{
  public:
    void myft()
    {
        cout<<"泛化版"<<endl;
    }

    template <typename T1>
    void myft1(T1 tmpt)
    {
        cout<<tmpt+1<<endl;
    }
};

//T和U都特化了，所以这里没有参数
template <>
class B<int,int>
{
    public:
        void myft()
        {
            cout<<"int，int全特化版本"<<endl;
        }
};

//T和U都特化了
template <typename T, typename U>
class B<const T,const U>
{
    public:
        void myft()
        {
            cout<<"const,const全特化版本"<<endl;
        }
};

//T和U都特化了
template <typename T, typename U>
class B<T *,U *>
{
    public:
        void myft()
        {
            cout<<"point,point全特化版本"<<endl;
        }
};

template <typename T, typename U>
class B<T &,U &>
{
    public:
        void myft()
        {
            cout<<"左值引用全特化版本"<<endl;
        }
};

//单独特化成员函数
template <>
void B<double,double>::myft()
{
    cout<<"double,double全特化版本"<<endl;
}

//偏特化，第一个参数特化了，所以这里没有参数
template <typename T>
class B<int,T>
{
    public:
    void myft()
        {
            cout<<"int，偏特化版本"<<endl;
        }
};


//函数模版全特化和偏特化版本
template<typename T, typename U>
void t_func(T t, U u)
{
    cout<<"函数泛化版本"<<endl;
}

//注意，将两个函数顺序调换，（int，int）版本调用的函数不一样，所以尽量避免让函数在调用的时候有歧义


template<typename M>
void t_func(int t, M u)
{
    cout<<"函数偏特化int版本"<<endl;
}

template<>
void t_func(int t, int u)
{
    cout<<"函数全特化int版本"<<endl;
}

//a模版类型改变可以特化
//b模版参数范围上改变都可以特化
//1、int到const int
//2、原来为T，现在为*T
//3、原来是T，现在是&T

int main()
{
    B <int,float> b;
    b.myft();
    B <int,int> b1;
    b1.myft();
    B <int *,int*> b2;
    b2.myft();
    B <double,double> b3;
    b3.myft();
    t_func(15.0, 17.0);
    int i = 15;
    int j = 16;
    t_func(i, j);
    t_func(15, 17.0);

}
