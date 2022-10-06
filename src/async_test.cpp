//
// Created by sxh on 2022/10/5.
//
/*
 * std::async 的使用以及 C++ 中异步操作的实现
 */
#include "iostream"
#include "future"
using namespace std;

int getDataDemo()
{
    cout << "数据查询开始" << " threadID:" << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::seconds(5));//模拟耗时
    return 100;
}
int main_async_test()
{
    //this_thread来引用当前线程   参考：https://blog.csdn.net/chengqiuming/article/details/89277072
    cout << "执行数据查询" << " threadID:" << this_thread::get_id() << endl;//表示是哪一个线程在运行
//    future<int> m_future = async(launch::async, getDataDemo);//异步执行
    future<int> m_future = async(launch::deferred, getDataDemo);//延迟执行
//  future<int> m_future = async(getDataDemo);//默认策略
    future_status m_status;
    do
    {
        m_status = m_future.wait_for(chrono::seconds(1));//c++的一个时间戳库，http://www.cncsto.com/article/81706.html
        switch (m_status)
        {
            case std::future_status::ready:
                cout << "数据查询完成" << " threadID:" << this_thread::get_id() << endl;
                break;
            case std::future_status::timeout:
                cout << "数据查询中..." << " threadID:" << this_thread::get_id() << endl;
                break;
            case std::future_status::deferred:
                cout << "数据查询延迟" << " threadID:" << this_thread::get_id() << endl;
                m_future.wait();
                break;
            default:
                break;
        }
    }while (m_status != future_status::ready);

    //对应在deferred：函数只有在 std:async 所返回的期值的 get 或 wait 得到调用时才执行、并且调用方会阻塞至运行结束，否则不执行。
    int ret = m_future.get();
    cout << "数据查询结果:"<< ret << " threadID:" << this_thread::get_id() << endl;

    system("pause");
    return 0;
}

