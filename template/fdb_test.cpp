/*
 * @Author: your name
 * @Date: 2020-08-15 10:03:21
 * @LastEditTime: 2020-08-27 17:17:09
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /cpp_train/template/fdb_test.cpp
 */
#include <vector>
#include "fdb_template.h"
#include <unistd.h>

using namespace::std;

int main()
{
    vector<fdb_unit> fdbs;
    Trade t = {1000, "trade",15.2,100,123,321};
    cout<<t.instrument_id<<""<<t.price<<endl;
    Fdb<Trade> ft0("test1");
    ft0.set_t(t);
    cout<<ft0.t.instrument_id<<endl;
    fdb_unit f1 = {FdbType::T, &ft0};
    cout<<((Fdb<Trade> *)(f1.fdb_p))->get_t().ask_no<<endl;
    fdbs.push_back(f1);
    Order o = {1000, "order",15.2,100};
    cout<<o.instrument_id<<""<<o.price<<endl;
    Fdb<Order> fo("test2");
    fo.set_t(o);
    fdb_unit f2 = {FdbType::O, &fo};
    fdbs.push_back(f2);
    for (auto iter = fdbs.cbegin(); iter != fdbs.cend(); iter++)
    {
        if (iter->tp == FdbType::T)
        {
            cout << "trade: "<<((Fdb<Trade> *)iter->fdb_p)->get_t().ask_no << endl;
        }
        else
        {
            cout << "order: "<<((Fdb<Order> *)iter->fdb_p)->get_t().price << endl;
        }
    }
    return 0;
}