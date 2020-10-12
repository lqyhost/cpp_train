#include <iostream>
#include <vector>
#include <map>

using namespace::std;

template <typename T>
struct map_s
{
    typedef std::map <std::string,T> s_t;
};

//C++ 11 用using给自己定义的模版起了一个别名
template <typename T>
using str_map_t = std::map <std::string,T>;

//显式指定函数模版类型
template <typename T>
using my_func_M = int(*)(T,T);

template <typename T>
T add_t(T a, T b)
{
    return a + b;
}

int main()
{
    //typedef 一般用于定义类型别名，实际上C++11中using也可以
    typedef unsigned int uint_t;
    uint_t a = 19;
    using uint_u_t = unsigned int;
    uint_u_t b = 19;
    typedef std::map<std::string, int> map_s_i;
    typedef std::map<std::string, std::string> map_s_s;
    map_s_i my_map1;
    my_map1.insert({"math", 120});
    map_s_s my_map2;
    my_map2.insert({"math", "120"});
    //需要定义一个模版类型，部分固定不变，部分自己指定
    map_s <int>::s_t ms_i;
    ms_i.insert({"math", 120});
    map_s <std::string>::s_t ms_s;
    ms_s.insert({"math", "120"});
    //使用using定义的模版
    str_map_t<int> ms_t_i;
    ms_t_i.insert({"math", 120});
    str_map_t<std::string> ms_t_s;
    ms_t_s.insert({"math", "120"});

    //显式指定模版类型
    my_func_M<int> add_t_i;
    add_t_i = add_t;
    cout<<add_t_i(13,9)<<endl;
    return 0;
}