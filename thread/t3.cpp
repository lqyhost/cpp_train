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

class D
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<100;i++)
        {
            unique_lock<mutex> my_guard(my_mutex, try_to_lock);
            chrono::milliseconds dura(500);
            std::this_thread::sleep_for(dura);//休息60s
            cout<<"recv d"<<i<<endl;
            msg_recv.push_back(i);
        }
    }
    //将消息队列取出
    void do_cmd()
    {

        for (int i = 0;i<100;i++)
        {
            if (!msg_recv.empty())
            {
                unique_lock<mutex> my_guard(my_mutex, try_to_lock);
                if(my_guard.owns_lock())
                {
                    chrono::milliseconds dura(1000);
                    std::this_thread::sleep_for(dura);//休息60s
                    int cmd = msg_recv.front();
                    msg_recv.pop_front();
                    cout<<"cmd d "<<cmd<<endl;
                    my_guard.unlock();
                    //do something without lock
                    my_guard.lock();
                }
                else
                {
                    cout<<"cant't lock do_cmd"<<endl;
                }

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
    //unlock 可以释放资源 在需要的时候重新lock，如果不调用，析构的时候会自动unlock
    //try_to_lock会尝试用mutex的lock去锁定，如果没有成功，也会立即返回
    D d;
    thread t7(&D::recv, &d);
    thread t8(&D::do_cmd, &d);
    t7.join();
    t8.join();
    //release() 返回uniquelock管理的mutext对象指针，并释放所有权，也就是二者不再有怒关系
    //注意unlock和release是有区别的
    //整体看起来unique_lock的控制粒度更细化，自由度更高
    //unique_lock是可以转移mutex的所有权的，但是不能复制
    mutex mutex1;
    unique_lock<mutex> sp_gard(mutex1);
    //unique_lock<mutex> sp_gard1(sp_gard);//error 不能复制所有权
    unique_lock<mutex> sp_gard1(std::move(sp_gard));//左值转右值，调用移动语义构造函数sp_gard指向空，sp_gard1指向mutext1
    return 0;
}