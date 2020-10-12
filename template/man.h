#ifndef MAN_H
#define MAN_H

#include <iostream>
#include <string>

// 类模版
template <typename T>
class man
{
public:
    man(T t): name(t)
    {

    }
    void printName();


    // 类模版的友元函数声明
    template <typename Q>
    friend void fprintMan(man<Q> & m);

    // 类模版的友元类声明
    template <typename Q>
    friend class printClass;

private:
    T name;
};

#endif