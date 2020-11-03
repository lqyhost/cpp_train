/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-20 07:26:32
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-21 17:13:25
 * @FilePath: /cpp_train/thread/t9.cpp
 */
#include <iostream>
#include <thread>
#include <future>
using namespace::std;


int t_thread(int n)
{
    int rt = 0;
    cout<<"this thread id:"<<this_thread::get_id()<<endl;
    for(int i = 0;i<n;i++)
    {
        rt += i;
        chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);//休息50ms
    }
    cout<<"this thread id:"<<this_thread::get_id()<<" end"<<endl;
    return rt;
}

int main()
{
    cout<<"main thread id:"<<this_thread::get_id()<<endl;
    //std::asynic
    //参数详述：函数模版，用于启动一个异步任务，启动后，返回一个std::future对象
    future<int> result = async(t_thread, 12);
    cout<<result.get();
    //std::launch::deferred 延迟调用，使用本参数线程在get或者wait调用的时候才会调用
    future<int> result1 = async(std::launch::deferred,t_thread, 12);
    //cout<<result1.get();//如果get/wait不调用，线程不会被创建
    //std::thread()创建线程，但是如果系统资源紧张，创建线程是可能失败的
    //asynic和thread最明显的区别是asynic有时候并不创建线程，有时候是在get调用的时候才会创建
    return 0;
}