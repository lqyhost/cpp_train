#include <iostream>
#include <vector>
#include <memory>

using namespace::std;

unique_ptr<string> tunpq()
{
    unique_ptr<string> pr(new string("test"));
    return pr;//返回局部对象时，系统会生成一个局部对象，调用unique_ptr构造函数
}

void my_delete(string *p)
{
    cout<<"my_delete"<<endl;
    delete p;
    p = nullptr;
}

int main()
{
    //虽然unique_ptr是独占的，但是当unique_ptr要销毁的时候，是可以拷贝的，所以可以用来做函数的返回值
    auto pr1 = tunpq();
    //指定删除器，缺省时默认delete,指定时格式为unique_ptr<指向对象类型，删除器> 智能指针变量名
    typedef void(*fp)(string *);//typedef定义一个函数指针，类型名为fp
    unique_ptr<string, fp> pr2(new string("test"), my_delete);
    using fp2 = void(*)(string *);//using定义一个函数指针，类型名为fp2
    unique_ptr<string, fp2> pr3(new string("test"), my_delete);
}