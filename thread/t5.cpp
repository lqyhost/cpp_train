#include <iostream>
#include <thread>
#include  <list>

using namespace::std;

class C
{
public:
    //将收到的消息加入到队列
    void  in_msg()
    {
        for (int i = 0;i<2000;i++)
        {
            cout<<"插入一个元素"<<i<<endl;
            unique_lock<mutex> my_guard(my_mutex);
            // chrono::milliseconds dura(50);
            // std::this_thread::sleep_for(dura);//休息50ms
            msg_recv.push_back(i);
        }
        return;
    }
    //检测消息队列是否为空
    bool out_msg(int &cmd)
    {
        if (!msg_recv.empty())
        {
            std::unique_lock<std::mutex> sbguaid1(my_mutex);
            if (!msg_recv.empty())
            {
                cmd = msg_recv.front();//返回第一个元素
                msg_recv.pop_front();//移除第一个元素
                return true;
            }
        }
        return false;
    }
    //将消息队列取出
    void do_cmd()
    {
        int command  = 0;

        for (int i = 0;i<2000;i++)
        {
            bool result = out_msg(command);
            if (result)
            {
                // unique_lock<mutex> my_guard(my_mutex);
                // chrono::milliseconds dura(50);
                cout<<"执行命令"<<command<<endl;
            }
            else
            {
                cout<<"消息队列为空"<<endl;
            }
        }
        cout<<"do_cmd end"<<endl;
    }
private:
    list<int> msg_recv;
    mutex my_mutex;
};

int main()
{
    //unique_lock 取代lock_guard
    //功能基本类似，一般lock_guard就可以了，lock_guard支持的参数，unique_lock都支持，unique_lock更加灵活，可选参数更多，内存占用多，效率差一些
    C c;
    thread t5(&C::do_cmd, &c);
    thread t6(&C::in_msg, &c);
    t6.join();
    t5.join(); //问题：为什么全部插入完了以后读取才开始

}