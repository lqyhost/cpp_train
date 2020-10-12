#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>

using namespace::std;

void my_func(const int i)
{
    cout<<"my thread start"<<endl;
    cout<<"i:"<<i<<endl;
    cout<<"my thread end"<<endl;
}

vector<int> ii = {1,2,34,43};

void my_func1(const int i)
{
    cout<<"my thread start"<<endl;
    cout<<"i:"<<i<<":"<<ii[3]<<endl;
    cout<<"my thread end"<<endl;
}

void my_func2(const int i)
{
    cout<<"my thread start"<<endl;
    cout<<"i:"<<i<<":"<<ii[3]<<endl;
    ii.push_back(i);
    cout<<"my thread end"<<endl;
}

class A
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<1000;i++)
        {
            cout<<"recv"<<i<<endl;
            msg_recv.push_back(i);
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
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

};

class B
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<1000;i++)
        {
            my_mutex.lock();
            cout<<"recv"<<i<<endl;
            msg_recv.push_back(i);
            my_mutex.unlock();
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
                my_mutex.lock();
                int cmd = msg_recv.front();
                msg_recv.pop_front();
                cout<<"cmd"<<cmd<<endl;
                my_mutex.unlock();
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


class C
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<1000;i++)
        {
            lock_guard<mutex> my_guard(my_mutex);
            cout<<"recv"<<i<<endl;
            msg_recv.push_back(i);
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
                lock_guard<mutex> my_guard(my_mutex);
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
        for (int i = 0;i<1000;i++)
        {
            my_mutex1.lock();//实际工作中，锁是在不同逻辑位置的
            my_mutex2.lock();
            cout<<"recv d "<<i<<endl;
            msg_recv.push_back(i);
            my_mutex2.unlock();
            my_mutex1.unlock();
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
                my_mutex1.lock();//解决互锁
                my_mutex2.lock();
                //my_mutex1.lock();
                int cmd = msg_recv.front();
                msg_recv.pop_front();
                cout<<"cmd d "<<cmd<<endl;
                my_mutex1.unlock();
                my_mutex2.unlock();
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
    mutex my_mutex1;
    mutex my_mutex2;
};

class E
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<1000;i++)
        {
            lock(my_mutex1,my_mutex2);
            cout<<"recv e "<<i<<endl;
            msg_recv.push_back(i);
            my_mutex1.unlock();
            my_mutex2.unlock();
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
                lock(my_mutex1,my_mutex2);
                //my_mutex1.lock();
                int cmd = msg_recv.front();
                msg_recv.pop_front();
                cout<<"cmd e "<<cmd<<endl;
                my_mutex1.unlock();
                my_mutex2.unlock();
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
    mutex my_mutex1;
    mutex my_mutex2;
};

class F
{
public:
    //将收到的消息加入到队列
    void  recv()
    {
        for (int i = 0;i<1000;i++)
        {
            lock(my_mutex1,my_mutex2);
            lock_guard<mutex> guard1(my_mutex1,std::adopt_lock);
            lock_guard<mutex> guard2(my_mutex2,std::adopt_lock);
            cout<<"recv e "<<i<<endl;
            msg_recv.push_back(i);
        }
    }
    //将消息队列取出
    void do_cmd()
    {
        for (int i = 0;i<1000;i++)
        {
            if (!msg_recv.empty())
            {
                lock(my_mutex1,my_mutex2);
                lock_guard<mutex> guard1(my_mutex1,std::adopt_lock);
                lock_guard<mutex> guard2(my_mutex2,std::adopt_lock);
                int cmd = msg_recv.front();
                msg_recv.pop_front();
                cout<<"cmd e "<<cmd<<endl;
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
    mutex my_mutex1;
    mutex my_mutex2;
};

int main()
{
    vector<thread> mythread;
    for (int i = 0; i < 10; i++)
    {
        mythread.push_back(thread(my_func,i));
    }
    for (auto iter = mythread.begin(); iter != mythread.end(); ++iter)
    {
        iter->join();
    }
    //运行可以看到，多个线程执行顺序是无序的，而且参数传递进去无法稳定使用
    //数据共享问题
    //只读数据
    vector<thread> mythread1;
    for (int i = 0; i < 10; i++)
    {
        mythread1.push_back(thread(my_func1,i));
    }
    for (auto iter = mythread1.begin(); iter != mythread1.end(); ++iter)
    {
        iter->join();
    }
    //有读有写
    //直接运行，代码崩溃，简单的处理就是读的时候不能写，写的时候也不能读
    // vector<thread> mythread2;
    // for (int i = 0; i < 10; i++)
    // {
    //     mythread2.push_back(thread(my_func2,i));
    // }
    // for (auto iter = mythread2.begin(); iter != mythread2.end(); ++iter)
    // {
    //     iter->join();
    // }
    //用成员函数来写线程
    //以下代码是不稳定的，因为数据有读有写
    // A a;
    // thread t1(&A::recv, &a);//第二个参数必须是引用，才能保证不同线程是用的同一个对象，而不是新生成的copy
    // thread t2(&A::do_cmd, &a);
    // t1.join();
    // t2.join();
    //保护共享数据，某个线程用代码将共享数据锁住，其他线程操作数据必须等待
    //互斥量（mutex），一个类对象，多个线程可以尝试用lock()成员函数来加锁定，只有一个线程可以锁定成功，会返回，如果没有锁成功，那么线程会卡在这里，线程使用完数据以后unlock()，会释放资源
    //lock()保护数据必须合适，在需要保护的范围要求中，尽可能少的保护，避免影响效率
    B b;
    thread t3(&B::recv, &b);
    thread t4(&B::do_cmd, &b);
    t3.join();
    t4.join();
    
    //为了防止忘记unlock()导致锁死，lock_guard(),在构造的时候偶lock，析构的时候unlock，可以直接取代lock()和unlock()
    C c;
    thread t5(&C::recv, &c);
    thread t6(&C::do_cmd, &c);
    t5.join();
    t6.join();
    //死锁
    //例如线程a锁定了ss资源，等待yy资源，然后被切换到线程b，线程b锁定了yy资源，等待ss资源，就会出现死锁
    D d;
    thread t7(&D::recv, &d);
    thread t8(&D::do_cmd, &d);
    t7.join();
    t8.join();
    //解决方案：只要保证多个锁的顺序一致，就不会死锁

    //std::lock() 一次锁住多个互斥锁量，如果有不满足的则等待，直到满足条件才继续
    //作为参数的互斥量在结束后需要调用unlock()
    E e;
    thread t9(&E::recv, &e);
    thread t10(&E::do_cmd, &e);
    t9.join();
    t10.join();

    //std::adopt_lock 在lock_guard的参数中添加std::adopt_lock作为参数，不再重新调用lock()构造
    //总的来说是用来避免忘记unlock，添加这个标记时，一定要在lock已经执行过的情况下
    cout<<"end of main"<<endl;
    return 0;
}