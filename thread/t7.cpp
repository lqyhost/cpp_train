/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-16 22:02:45
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-20 07:18:31
 * @FilePath: /cpp_train/thread/t7.cpp
 */
#include <iostream>
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

void my_thread(std::promise<int> &tmpp, int calc)
{
    //可以做一些列运算
    int rt = 0;
    cout<<"this thread id:"<<this_thread::get_id()<<endl;
    for(int i = 0;i<calc;i++)
    {
        rt += i;
        chrono::milliseconds dura(50);
        std::this_thread::sleep_for(dura);//休息50ms
    }
    cout<<"this thread id:"<<this_thread::get_id()<<" end"<<endl;
    tmpp.set_value(rt);//返回值保存到tmpp
    return;
}

void my_thread1(std::future<int> &ful)
{
    cout<<"my_thread1: "<<ful.get()<<endl;
}

int main()
{
    //std::async、std::future创建任务并返回值
    //希望线程返回一个结果
    //std::async 函数模版，用于启动一个异步任务，启动后，返回一个std::future对象
    //异步任务，就是自动创建一个线程，并开始执行对应的线程入口函数
    //std::future对象中含有线程入口函数返回的结果，准确的说就是线程返回的结果，可以用过get()函数获得返回的结果,实现一个访问异步操作结果的机制
    //结果保存在future，这个结果可能不能马上拿到，但是在一段时间，线程执行完毕的时候可以拿到结果
    cout<<"main"<<this_thread::get_id()<<endl;
    std::future<int> result = std::async(t_thread,20);
    //std::async和thread参数是一样的，也可以用类成员作为指针
    cout<<"main runing"<<endl;
    int def = 0;
    cout<<result.get()<<endl;//如果本句执行的时候线程还没有返回，程序会卡在这里。比较好的结果是主程序在get的时候基本上出结果了
    //get()只能使用一次
    //即便不调用get，整个程序还是会等待线程执行完毕才会退出
    //可以额外传递std::launch::deferred 表示线程如果函数被延迟到std::futurede wait()或者get()函数执行才开始执行
    std::future<int> result1 = std::async(std::launch::deferred,t_thread,20);
    cout<<result1.get()<<endl;//使用了std::launch::deferred，但是不调用get函数的话，线程根本不会创建，如果创建会是在主线程中直接运行
    std::future<int> result2 = std::async(std::launch::async,t_thread,20);
    cout<<"result2:"<<result2.get()<<endl;//使用了std::launch::async,在调用async函数的时候就开始调用线程函数，无论是否调用get函数线程都会运行，实际上系统默认就是async，所以第一个参数可以省略，在os系统下运行，1和3线程号是一样的
    cout<<"main end"<<endl;

    //std::package_task 打包任务
    //类模版，模版的参数是可调用对象，方便将来作为线程入口函数
    std::packaged_task<int(int)> mypt(t_thread);//相当于将函数包装起来,包装的好处主要是可以用于获取未来返回值
    std::thread t1(std::ref(mypt),10);
    t1.join();
    std::future<int> result3 = mypt.get_future();
    cout<<"result3:"<<result3.get()<<endl;
    std::packaged_task<int(int)> mypt1(t_thread);
    mypt1(33);//包装后也可以直接执行
    std::future<int> result4 = mypt1.get_future();
    cout<<"result4:"<<result4.get()<<endl;

    //std::promise类模版,myprom可以用于保存一个值，在某个线程中给他赋值,然后可以在其他线程中取用结果
    std::promise<int> myprom;
    std::thread t5(my_thread, std::ref(myprom),35);
    t5.join();

    //一种方式直接获取结果
    std::future<int> ful = myprom.get_future();//promise和future绑定，用于获取线程返回值
    // cout<<"result5: "<<ful.get()<<endl;
    //一种方式传递到另外的线程使用
    std::thread t6(my_thread1,std::ref(ful));
    t6.join();

    std::future<int> result5 = std::async(t_thread,20);
    cout<<"result5 21"<<result5.get()<<endl;
    cout<<"t_thread 20"<<std::async(t_thread,20).get()<<endl;
    //使用wait_for返回一个枚举型状态，返回子线程执行状态。这里可用于必须等待子线程的时候，如果有多个子线程，需要等待某个子线程的时候，可以使用这个函数
    std::future<int> result6 = std::async(t_thread,25);
    std::future_status status = result6.wait_for(std::chrono::seconds(6));
    if (status == std::future_status::timeout )
        cout<<"time out"<<endl;
    else if  (status == std::future_status::ready )
    {
        cout<<"ready"<<endl;
        cout<<"ready"<<result6.get()<<endl;
    }
    else if  (status == std::future_status::deferred )
        cout<<"deferred"<<endl;
    //当条件定义为deferred的时候，实际上线程是在get()函数调用的时候直接在主线程执行的，所以这里的wait_for并不会生效，子线程id等于主线程，一般不会这么用，这样等效与函数调用，不需要额外使用线程
    std::future<int> result7 = std::async(std::launch::deferred,t_thread,25);
    std::future_status status7 = result7.wait_for(std::chrono::seconds(2));
    if  (status7 == std::future_status::deferred )
    {
        cout<<"run in main"<<endl;
        cout<<"ready"<<result7.get()<<endl;
    }
        
    return 0;
}