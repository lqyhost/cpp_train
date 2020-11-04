/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-21 14:19:10
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-21 14:39:06
 * @FilePath: /cpp_train/thread/test.cpp
 */
#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>

using namespace::std;
bool sign = false;
int t_thread(int n)
{
    int rt = 0;
    cout<<"this thread id:"<<this_thread::get_id()<<endl;
    for(int i = 0;i<n;i++)
    {
        rt += i;
        chrono::milliseconds dura(500);
        std::this_thread::sleep_for(dura);//休息50ms
    }
    sign = true;
    cout<<"this thread id:"<<this_thread::get_id()<<" end"<<endl;
    return rt;
}

int time_out_check(int n)
{
    chrono::milliseconds dura(1000*n);
    std::this_thread::sleep_for(dura);//休息50ms
    if (sign == true)
    {
        cout<<"right"<<endl;
        return 1;
    }
    else
    {
        cout<<"error"<<endl;
        return 0;  
    }
}

int main()
{
    thread my_thread1(t_thread,2);
    thread my_thread2(time_out_check,2);
    my_thread1.join();
    my_thread2.join();
    return 0;
}