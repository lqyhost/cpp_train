#include <iostream>
#include <thread>

using namespace::std;

void my_func(const int &i, char *pc)
{
    cout<<"my_func"<<endl;
    cout<<i<<endl;
    cout<<pc<<endl;
}

void my_func1(const int i, const string &pc)
{
    cout<<"my_func"<<endl;
    cout<<i<<endl;
    cout<<pc.c_str()<<endl;
}

class A
{
public:
    void thread_work()
    {
        cout<<"thread_work"<<endl;
    }
};


int main()
{
    //线程使用中容易犯错的地方
    //传递临时对象作为线程参数
    int i = 234;
    int &my_i = i;
    char my_char[] = "this is test";
    thread my_thread(my_func, my_i, my_char);
    my_thread.join();
    //传递临时对象作为线程参数要避免的陷阱
    thread my_thread1(my_func, my_i, my_char);
    //my_thread1.detach();//主线程结束如果使用detach的方式，不推荐用引用，不要用指针，容易导致内存泄漏
    my_thread1.join();//可能使用同一片地址导致错误
    thread my_thread2(my_func1, my_i, string(my_char));
    //my_thread2.detach();
    my_thread2.join();
    //结论，不要轻易使用detach
    //使用类的成员函数作为线程函数
    A a;
    thread my_thread3(&A::thread_work,a);
    my_thread3.join();
    cout<<"end"<<endl;
    return 0;
}