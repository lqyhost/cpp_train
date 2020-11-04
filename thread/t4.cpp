#include <iostream>
#include <thread>

using namespace::std;

mutex a_mutex;

class A
{
private:
    A(){}
    static A *my_a;//静态成员变量
public:
    static A *get_instance()
    {
        // std::unique_lock<mutex> a_lock(a_mutex);//写法一，这种方式不好，因为每次调用函数都会加锁
        // if(my_a == NULL)
        // {
        //     my_a = new A;

        // }
        if(my_a == NULL)//写法二，只在空的时候加锁，如果只有一个if的话，可能一个线程new的时候，已经有其他的在等待锁了
        {
            std::unique_lock<mutex> a_lock(a_mutex);//因为有锁，所以其他的线程必须等待，等到锁解除的时候my_a以及赋予了初始值
            if(my_a == NULL)
            {
                my_a = new A;
                static a_release ar;//当类析构时，这个对象会调用析构函数，从而释放my_a
            }
        }
        return my_a;
    }
    static A *get_instance1()
    {
        if(my_a == NULL)
        {
            my_a = new A;

        }
        return my_a;
    }
    class a_release//类中嵌套类来实现释放内存
    {
    public:
        ~a_release()
        {
            if (A::my_a != NULL)
            {
                delete A::my_a;
                A::my_a = NULL;
            }
        }
    };
    void func()
    {
        cout<<"test"<<endl;
    }
};

//类静态变量初始化,必须
A *A::my_a = NULL;

int main()
{
    A *pa = A::get_instance();
    pa->func();
    A *pb = A::get_instance();
    pb->func();
    //call_once()保证在多个线程中，这个函数只调用一次
    return 0;
}