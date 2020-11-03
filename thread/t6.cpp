/*
 * @Description: 
 * @Author: lqyhost
 * @Github: https://github.com/lqyhost
 * @Date: 2020-10-16 07:57:00
 * @LastEditors: lqyhost
 * @LastEditTime: 2020-10-16 21:37:45
 * @FilePath: /cpp_train/thread/t6.cpp
 */
#include <iostream>
#include <thread>
#include  <list>

using namespace::std;


//线程一般谁先创建先执行
class C
{
public:
    //将收到的消息加入到队列
    void  in_msg()
    {
        for (int i = 0;i<200;i++)
        {
            cout<<"插入命令: "<<i<<endl;
            unique_lock<mutex> my_guard(my_mutex);
            // chrono::milliseconds dura(50);
            // std::this_thread::sleep_for(dura);//休息50ms
            msg_recv.push_back(i);
            //notify_one，调用条件变量通知一个另外的线程，唤醒wait
            my_cond.notify_one();
            //my_cond.notify_all();//调用条件变量通知其他所有的线程
        }
        return;
    }
    //检测消息队列是否为空
    bool out_msg(int &cmd)
    {
        return false;
    }
    //将消息队列取出
    void do_cmd()
    {
        int command  = 0;
        while(true)
        {
            unique_lock<mutex> my_guard(my_mutex);
            //wait 是条件变量的成员函数，用来等待，参数一为锁，参数二为返回bool值的lamba表达式，如果第二个返回flase，wait讲解锁，并堵塞到本行，直到其他某个线程调用notify_one()，wait才会解除阻塞，如果第二个参数返回值为true，那么wait直接返回
            //如果wait没有第二个参数，比如my_cond.wait(my_guard)那么就和第二个参数一直返回false一样，就是一直等待其他某个线程调用notify_one()
            //a、wait被唤醒以后，首先会尝试获取互斥锁，所以前面通知以后应立刻释放锁，否则会重新进入阻塞，如果获取到锁，则会加锁
            //如果wait有第二个参数，则判断第二个参数的表达式结果，如果为false，则wait则解锁重新阻塞，如果为true，则继续，如果没有第二个参数，则直接继续
            my_cond.wait(my_guard,[this]
            {
                if(!msg_recv.empty())
                    return true;
                return false;
            });
            //如果流程可以向下，则继续
            cout<<"thread_id:"<<std::this_thread::get_id()<<endl;//输出线程id
            cout<<"执行命令: "<<msg_recv.front()<<endl;//返回第一个元素
            msg_recv.pop_front();//移除第一个元素
            my_guard.unlock();//unique_lock是可以随时解锁的，如果取到数据了，后续处理逻辑又比较复制，可以提前解开锁定，再进行后面的数据处理
            //这个程序也可以改写成，被notify的时候，将队列中的消息都处理完
            // while(!msg_recv.empty())
            // {
            //     cout<<"执行流动命令: "<<msg_recv.front()<<endl;//返回第一个元素
            //     msg_recv.pop_front();//移除第一个元素
            // }
        }
        cout<<"do_cmd end"<<endl;
    }
private:
    list<int> msg_recv;
    mutex my_mutex;
    std::condition_variable my_cond;//生成条件变量对象，需要和互斥量配合使用
};

int main()
{
    //unique_lock 取代lock_guard
    //功能基本类似，一般lock_guard就可以了，lock_guard支持的参数，unique_lock都支持，unique_lock更加灵活，可选参数更多，内存占用多，效率差一些

    //条件变量 std::condition_variable、wait()、notify_noe()
    //假设有两个线程，a和b
    //在线程a中等待一个条件满足
    //线程b是往队列中加入消息的
    //前面的例子里面，需要反复判断数据列表是否为空，本例修改模式为当消息队列中有消息的时候，线程b可以通知线程a，a结束等待，开始继续执行
    //std::condition_variable 实际上是一个类，是一个条件相关类，等待条件达成触发
    C c;
    thread t6(&C::do_cmd, &c);
    //thread t7(&C::do_cmd, &c);//多个线程就需要通过notify_all来一次都唤醒，如果用notify_one就会随机唤醒其中的线程
    //当然，本例中两个线程是做同样的工作，实际工程中，可能是两个线程是做不同的工作
    thread t5(&C::in_msg, &c);
    t5.join();
    t6.join(); //问题：为什么全部插入完了以后读取菜开始
    //t7.join();
    return 0;
}

//本程序还又一个问题，由于out程序输出最后一个命令以后，参数二返回的又是false，也没有通知过来解锁，所以线程会一直阻塞在wait中
//次程序不是轮流执行，实际上，有时候唤醒以后，不一定wait获取锁一定能获取成功，因为输入消息的信息线程也在获取锁
//如果执行命令的线程执行时间比较长，并没有在wait中等待，唤醒也不是一定能唤醒wait的


//******在主代码里面加多线程，或者其他不是很有把握的程序时，可以先写一些逻辑代码，验证和测试确认功能以后，然后再加入系统*******