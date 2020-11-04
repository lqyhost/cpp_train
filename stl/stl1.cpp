#include "stl1.h"

//C++标准库C++ standard library 只要安装了C++编译器就可以用
//标准模版库 standard template library 包含在C++标准库，C++标准库的核心，是用范型编程的编码方式便携的一套库
//要了解 栈（先进后出） 队列（先进先出） 链表（有next指针）

//hash表是在一定空间中，通过hash映射到地址，查找比较快，当元素数量大于hash地址时，hash地址会倍增，然后产生新序列

int main()
{
    //容器分类
    //sequence containers顺序容器,比如 array vector deque list forward_list
    //associative containers关联容器 元素为键值对，适合查找，比如 set mutiset map mutimap，可能用树，也可能用哈希表实现
    //unordered containers无序容器，元素的位置不重要，重要的是元素是否在这个容器中，unordered_set unordered_multiset unordered_map unordered_mutimap 实际上也是一种关联容器,一般用哈希表实现
    //容器的应用
    //array 大小是固定的,内存空间是连续的
    _nmsp1::func();
}