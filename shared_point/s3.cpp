#include <iostream>
#include <vector>
#include <memory>
using namespace::std;

shared_ptr<int> creat_p(int value)
{
    return make_shared<int>(value);
}

shared_ptr<int> my_func(int value)
{
    shared_ptr<int> p_tmp = creat_p(value);
    return p_tmp;
}

void proc(shared_ptr<int> ptr)
{
    return;
}
//enable_shared_from_this<A> 模版类
class A:public enable_shared_from_this<A>
{
public:
    shared_ptr<A> get_self1()
    {
        return shared_from_this();//正确
    }
    shared_ptr<A> get_self2()
    {
        return shared_from_this();//正确
    }
};

int main()
{
    //my_func(15); 如果没有接受返回值，则返回时候，引用计数归零，直接销毁
    auto p = my_func(15);//临时变量被p指向，所以不会被销毁，比直接返回引用更安全，数据使用完以后会自动销毁
    //慎用裸指针
    //一个普通的指针绑定到shared_ptr以后，内存管理的指责已经转给shared_ptr了，不要直接操作了
    int *pk = new int(100);//裸指针
    //proc(p);//语法错误，不能转换
    proc(shared_ptr<int>(pk));//不报错，参数是临时shared_ptr，用裸指针显式生成，但是在函数返回的时候，由于计数归零，内存会被回收
    *p = 45;//本来是可以的，但是由于内存已经被回收了，这时候会导致不可知错误
    shared_ptr<int> p2(pk);
    proc(p2);//这样就可以
    //绝对不要用裸指针初始化多个shared_ptr
    int *pp = new int(100);
    shared_ptr<int> p1(pp);
    //shared_ptr<int> p2(p);//释放其中一个shared_ptr的时候，内存会被释放，下次再释放的时候就有问题
    shared_ptr<int> ps2(p1);
    //不能将get返回的指针直接delete
    shared_ptr<int> sp1(new int(100));
    int *pd = sp1.get();
    //delete p;//会导致异常
    //不能将get返回的指针绑定到另外一个shared_ptr，原理为裸指针多处绑定
    //不要把类对象指针this作为shared_ptr返回，改用enable_shared_from_this
    shared_ptr<A> pa1(new A);
    shared_ptr<A> pa2(pa1);//没问题，两个计数
    //shared_ptr<A> pa3 = pa1->get_self1();//异常，计数都只有一次，但是指向地址一只，导致内存被释放两次，也是裸指针问题
    shared_ptr<A> pa3 = pa1->get_self2();//正确
    
    //移动语意，使用移动比复制要快，在处理较大或者多次赋值时更快
    shared_ptr<int> pi1(new int(1000));
    shared_ptr<int> pi2(std::move(pi1));//移动构造新的指针对象，pi1不再指向原来的对象，而是空，pi2指向该指针，计数为一
    shared_ptr<int> ppp3;
    ppp3 = std::move(pi2);//移动赋值，pi2不再指向原来的对象，而是空，pi3指向该指针，计数为一
}