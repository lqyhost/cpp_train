#include <iostream>
#include <thread>
#include  <list>

using namespace::std;

class C
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<20;i++)
        {
            unique_lock<mutex> my_guard(my_mutex);
            chrono::milliseconds dura(1000);
            std::this_thread::sleep_for(dura);//休息60s
            cout<<"recv"<<i<<endl;
            msg_recv.push_back(i);
        }
    }
    //将消息队列取出
    void do_cmd()
    {

        for (int i = 0;i<20;i++)
        {
            if (!msg_recv.empty())
            {
                unique_lock<mutex> my_guard(my_mutex);
                chrono::milliseconds dura(1000);
                std::this_thread::sleep_for(dura);//休息60s
                int cmd = msg_recv.front();
                msg_recv.pop_front();
                cout<<"cmd"<<cmd<<endl;
            }
            else
            {
                cout<<"empty"<<endl;
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
    thread t5(&C::recv, &c);
    thread t6(&C::do_cmd, &c);
    t5.join();
    t6.join();
    //条件变量 std::condition_variable、wait()、notify_noe()
    //假设有两个线程，a和b
    //在线程a中等待一个条件满足
    //线程b是往队列中加入消息的
    //当消息队列中有消息的时候，线程b可以通知线程a，a结束等待，开始继续执行
}