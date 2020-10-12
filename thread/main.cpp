#include <iostream>
#include <thread>

using namespace::std;

void my_func()
{
    cout<<"my thread start"<<endl;
    //
    cout<<"my thread end"<<endl;
}

class TA
{
public:
    int ta_i;
    TA(int &i):ta_i(i){}
    void operator()()//不能带参数
    {
        cout<<"my thread start"<<endl;
        cout<<ta_i<<endl;
        cout<<"my thread end"<<endl;
    }
};

int main()
{
    //并发、进程、线程
    //并发：两个或者更多的任务同时发生：一个程序同时执行多个任务。通过任务切换实现，并发需要做上下文切换，本身是有时间开销的
    //进程：运行起来的可执行程序，进程有自己独立的运行空间
    //线程：程序运行的最小单位、程序最少有一个主线程，用户可以根据需求创建多个线程，实现同时完成多个工作的目的，所有线程共享同一片内存空间
    //多线程可以共享内存空间，开销小于多进程
    //线程不是越多越好，每个线程都需要一个独立的堆栈空间（1M），线程切换会需要保存中间状态，切换本身有时间开销
    //线程共享内存也会带来数据一致性的问题
    //C++ 11 新标准直接支持多线程支持，强化了平台移植的工作量
    thread my_thread(my_func);//thread接受一个可调用对象
    cout<<"befor thread start"<<endl;
    if (my_thread.joinable())
        my_thread.join();//join以后线程开始执行
    cout<<"after thread end"<<endl;
    //join 有主线程等待子线程执行完后才结束的功能
    int i =15;
    TA ta(i);
    thread my_thread1(ta);//类对象作为线程调用对象
    my_thread1.join();
    //lambda表达式
    auto my_lambdathread = []
    {
        cout<<"my_lambdathread"<<endl;
    };
    thread my_thread2(my_lambdathread);//类对象作为线程调用对象
    my_thread2.join();
    return 0;
}