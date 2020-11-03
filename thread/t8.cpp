/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-20 07:26:32
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-20 17:45:19
 * @FilePath: /cpp_train/thread/t8.cpp
 */
#include <iostream>
#include <thread>
using namespace::std;

int g_mount = 0;
atomic<int> g_mount_a = 0;

int COUNT = 20000000;

void t0()
{
    for (int i = 0; i < COUNT; i++)
    {
        g_mount ++;
    }
}

std::mutex my_mutex;

void t0_1()
{
    for (int i = 0; i < COUNT; i++)
    {
        my_mutex.lock();
        g_mount ++;
        my_mutex.unlock();
    }
}

void t0_2()
{
    for (int i = 0; i < COUNT; i++)
    {
        g_mount_a ++;
        //g_mount_a = g_mount_a +1;//如果这么写就回出错，原子操作适合++，--，+=等操作符，其他的表达式应先测试以后使用
    }
}

int main()
{
    //原子操作 std::atomic
    //互斥量是在多线程中保护共享数据
    //两个线程对一个变量进行操作,即便一个读一个写，也会出现问题，因为一句写操作或者一句读操作执行的时候也是多句汇编代码
    // thread my_thead2(t0);
    // thread my_thead1(t0);
    //上面的代码执行错误，因为可能异步操作错误
    // thread my_thead2(t0_1);
    // thread my_thead1(t0_1);
    //修改以后执行正确，但是运行时间明显增加，效率比较低，可以使用原子操作更高效
    //原子操作是在多线程中不会被打断的程序片段，可实现无锁的多线程并发，效率更高
    //互斥量适应一段代码，原子操作适应一个变量的运算读写
    thread my_thead2(t0_2);
    thread my_thead1(t0_2);
    my_thead1.join();
    my_thead2.join();
    cout<<"after run"<<g_mount<<endl;
    cout<<"after run"<<g_mount_a<<endl;
    return 0;
}