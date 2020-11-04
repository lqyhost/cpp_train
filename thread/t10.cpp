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
            msg_recv.push_back(i);
            my_cond.notify_one();
        }
        return;
    }
    //将消息队列取出
    void do_cmd()
    {
        int command  = 0;
        while(true)
        {
            unique_lock<mutex> my_guard(my_mutex);
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
            my_guard.unlock();//unique_lock是可以随时解锁的，如果取到数据了，后续处
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

    C c;
    thread t6(&C::do_cmd, &c);
    thread t5(&C::in_msg, &c);
    t5.join();
    t6.join();
    //wait的虚假唤醒，被唤醒的时候，被没有收到数据，在程序中，wait的第二个参数lambda表达式判断了数据是否为空，避免了虚假唤醒，编程应该注意，避免虚假唤醒以后操作导致数据错误
    
    //线程池
    //假设有一个服务器程序，每来连进来一个客户端，就创建一个线程为客户提供服务
    //如果是网络游戏，用户数量巨大，上面的方式就不适应，创建线程以及线程切换是需要消耗内存和cpu资源的
    //不断创建线程，也会影响系统稳定性
    //基于以上场景，使用线程池的概念，将多个线程统一管理，使用的时候取出来，使用完放回去，并不释放资源
    //实现方法，在程序启动时，一次性创建一定数量的线程，当任务来的时候，抓取空闲线程直接使用，如果没有空闲线程，则任务等待。在运行过程中，不进行线程的创建和销毁，提高系统稳定性，降低资源消耗

    //线程创建数量
    //一个程序运行起来，一般2000个线程是线程数量极限
    //接口提供商会提供线程数量建议，比如=cpu数量，cpu数*2，cpu数*2+2
    //一个线程是一个执行通路，可以根据业务量，至少应该大于堵塞性线程的服务数量
    //即使有业务需求，线程最好也控制在500个以内，如果能压缩在200以内更好，另外可以使用代码进行测试以后再确定

    return 0;
}
