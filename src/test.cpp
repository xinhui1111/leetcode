//
// Created by sxh on 2022/10/19.
//
/*
 * 使用"{ }"限定lock_guard作用域
 * lock_guard在创建的时候加锁，在delete的时候释放的锁
 * 两种创建锁的方式：
 *  1.lock_guard(mutex& m, adopt_lock);
 *  2.lock_guard(mutex& m);
 *这两种创建其实没你什么区别，关键要注意，创建的时候就会去获取锁，然后生命周期之外就会对锁进行释放，所以关注生命周期在哪，这里第一个使用了{},所以生命
 * 周期就是在{}内，而第二个使用了while循环，那么前一次循环结束了就代表了此次生命周期的结束
 * 参考：https://blog.csdn.net/gehong3641/article/details/124028976
 */
#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <ctime>
#include <thread>
#include <cstdio>

using namespace std;

// 时间模拟消息
string mock_msg()
{
    char buff[30] = { 0 };
    static int i = 100000;
    //sprintf_s( buffer, 200, " String: %s\n", s );将" String: %s\n"写入到了buffer中，并且其中了s将%s的部分替代了，限定了长度200，不会发生溢出
//    snprintf(s,100,"%.*S",3,"abcd");将"%.*S"写入到s中，并限定长度为100
//    sprintf(buff, "%d"，i--);
    snprintf(buff, sizeof (buff)/ sizeof(int),"%d  %d", i--);//数组没有在函数里传参是可以这么计算的，否则是不可以被
    return buff;
}

class CMutexTest
{
public:
    void recv_msg(); //接收消息
    void read_msg(); //处理消息
private:
    vector<string> msg_queue; //消息队列，用vector实现的消息队列，关键实现的功能就行
    mutex m_mutex;	//互斥量
};

// 模拟接收消息
void CMutexTest::recv_msg()
{
    while (true)
    {
        string msg = mock_msg();
        cout << "recv the msg " << msg << endl;

        // 使用"{ }"限定lock_guard作用域
        {
            lock_guard<mutex> mylockguard(m_mutex);
            // 消息添加到队列
            msg_queue.push_back(msg);
        }
        this_thread::sleep_for(chrono::milliseconds(10));//方便观察数据
    }
}

// 模拟读取处理
void CMutexTest::read_msg()
{
    while (true)
    {
        // 已经加锁
        m_mutex.lock();
        // 传递所有权给lock_guard,并传入adopt_lock表示已获得所有权
        lock_guard<mutex> mylockguard(m_mutex, adopt_lock);//adopt_lock:用于使作用域锁定取得锁定互斥的所有权的标记，一个循环周期就会结束
        if (!msg_queue.empty())
        {
            // 处理消息并移除
            string msg = msg_queue.front();
            cout << "read the msg " << msg << endl;
            msg_queue.erase(msg_queue.begin());
        }
        this_thread::sleep_for(chrono::milliseconds(15));//方便观察数据
    }
}

int main_test()
{
    CMutexTest my_test;
    thread recv_thread(&CMutexTest::recv_msg, &my_test); //接收线程
    thread read_thread(&CMutexTest::read_msg, &my_test); //处理线程

    recv_thread.join();
    read_thread.join();
}


