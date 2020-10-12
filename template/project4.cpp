#include <iostream>
#include <vector>

using namespace::std;

//普通类的模版函数
class A
{
  public:
  template <typename T>
  void myft(T tmpt)
  {
      cout<<tmpt<<endl;
  }
};

//类模版的成员函数模版
template <typename T>
class B
{
  public:
  void myft(T tmpt)
  {
      cout<<tmpt<<endl;
  }
  template <typename T1>
  void myft1(T1 tmpt)
  {
      cout<<tmpt+1<<endl;
  }
};

//为了避免在多个cpp文件中都实例化相同的类模版实例，C++11提供了显式实例化，在使用模版的cpp中如下定义
//template B<float>;

int main()
{
    A a;
    a.myft(1244);
    B <int>b;
    b.myft(1244);
    b.myft1(1244);
}
