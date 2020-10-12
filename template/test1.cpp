
#include <iostream>
#include <vector>
using namespace std;
struct ST
{
    int a;
    int b;
    ST()  //默认构造函数
    {
        a = 0;
        b = 0;
    }
    
    void set(ST* s1,ST* s2)//赋值函数
    {
        s1->a = s2->a;
        s1->b = s2->b;
    }
    ST& operator=(const ST& s)//重载运算符
    {
        set(this,(ST*)&s);
    }
    ST(const ST& s)//复制构造函数
    {
        *this = s;  
    }
};
int main()
{
    ST a ;  //调用默认构造函数
    a.a = 15;
    a.b = 18;
    vector<ST> v;
    v.push_back(a);  //调用复制构造函数
    ST s = v.at(0);  //调用=函数
    cout << s.a <<"  " << s.b << endl;
    cin >> a.a;
    return 0;
}