#include <iostream>
#include <vector>
#include <memory>
using namespace::std;

class A
{

};

int main()
{
    //weak_ptr 指向一个又shared_ptr管理的对象，但是指向的对象不计weak_ptr数，也就是不控制对象的生命周期，所以它不是独立的智能指针，不能操作指向的资源,可以监视shared_ptr是否存在
    //shared_ptr释放对象不受weak_ptr的影响
    shared_ptr<int> pi1(new int(1000));
    weak_ptr<int> piw1(pi1);//piw1弱共享pi1 强引用计数改变，弱引用计数加1
    weak_ptr<int> piw2 = pi1;
    //lock() 如果weak_ptr所指向的对象存在，则返回一个shared_ptr，且对象指针计数加一，否则返回空的shared_ptr
    auto pi2 = piw2.lock();
    if(pi2 != nullptr)
    {
        cout<<*pi2<<endl;
    }
    //expired() 所指向的对象是否还存在
    pi1.reset();
    pi2.reset();
    if(piw2.expired())
    {
        cout<<"expired"<<endl;
    }
    return 0;
}