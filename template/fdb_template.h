#include <iostream>
#include <string>
#include <string.h>

/******************************
 * 构建一个数据结构，包含类型信息和void *指针
 * 构建一个该数据结构表，构建以后只增不减，直到结构完整释放
 * 问题
 * 1、存在内存泄露的可能
 * 2、有需要运行过程中增减，修改表的要求
*******************************/


const int INSTRUMENT_ID_LEN = 16;
const int DATE_LEN = 9;

enum class FdbType: int8_t
{
    T,
    O
};

//逐笔委托行情
struct Order
{
    int64_t up_data_time;
    char instrument_id[INSTRUMENT_ID_LEN];       //合约、股票代码
    double price;                                //委托价格
    int32_t volume;                              //委托数量

    void set(Order* s1,Order* s2)//赋值函数
    {
        s1->up_data_time = s2->up_data_time;
        strcpy(s1->instrument_id, s2->instrument_id);
        s1->price = s2->price;
        s1->volume = s2->volume;
    }
    Order& operator=(const Order& s)//重载运算符
    {
        set(this,(Order*)&s);
    }
    // Order& operator=(const Order& s)//重载运算符
    // {
    //     this->up_data_time = s.up_data_time;
    //     strcpy(this->instrument_id, s.instrument_id);
    //     this->price = s.price;
    //     this->volume = s.volume;
    // }
};

//逐笔成交行情
struct Trade
{
    int64_t up_data_time;
    char instrument_id[INSTRUMENT_ID_LEN];       //合约、股票代码
    double price;                                //委托价格
    int32_t volume;                              //委托数量
    int64_t bid_no;                              //买方订单号
    int64_t ask_no;                              //卖方订单号
    Trade& operator=(const Trade& s)//重载运算符
    {
        this->up_data_time = s.up_data_time;
        strcpy(this->instrument_id, s.instrument_id);
        this->price = s.price;
        this->volume = s.volume;
        this->bid_no = s.bid_no;
        this->ask_no = s.ask_no;

    }
};



template<class T>
class Fdb
{
public:
    Fdb(std::string fdb_name): name(fdb_name){}
    ~Fdb();
    T get_t()
    {
        return t;
    }
    void set_t(T t)
    {
        this->t = t;
    }
public:
    std::string name;
    T t;
};

template<class T>
Fdb<T>::~Fdb()
{

}

struct fdb_unit
{
    FdbType tp;
    void * fdb_p;
};