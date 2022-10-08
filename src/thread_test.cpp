//
// Created by sxh on 2022/10/4.
//

/*
 * 线程同步方法
 */
#include <iostream>
#include <thread>


static int N = 0;

void fun(int n) {
    int t = 0;
    for (int i = 0; i < n; ++i) {
        ++t;
        ++N;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "local: " << t << std::endl;
    std::cout << "global: " << N << std::endl;
}

class C {
public:
    void fun(int n) {
        int t = 0;
        for (int i = 0; i < n; ++i) {
            ++t;
            ++_N;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "local: " << t << std::endl;
        std::cout << "global: " << _N << std::endl;
    }

    int _N;  // 这里的_N相对于fun函数是全局的！！！！！！！
};


int main_thread() {
    // 函数的例子
    std::cout << "function example:\n";
    std::thread t1(fun, 100000);
    std::thread t2(fun, 200000);
    t1.join();
    t2.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 类的例子
    std::cout << "\nclass example:\n";
    C c;
    c._N = 0;
    std::thread t3(&C::fun, &c, 100000);
    std::thread t4(&C::fun, &c, 20000);
    t3.join();
    t4.join();

    return 0;
}


//实现线程异步运行
/*
 * https://blog.csdn.net/qq_42302962/article/details/123433803
 *
 * 1.利用条件变量的通知与唤醒
 * 2.使用async传递结果
 */
#include <mutex>
#include <condition_variable>
#include <vector>
#include <numeric>
#include <future>

int res = 0;                        //保存结果的全局变量
std::mutex mu;                        //互斥锁全局变量
std::condition_variable cond;       //全局条件变量   wait是等待获取锁，而通知则是开启线程锁

//进行求和
/*
 * 进行求和
 */
void accumulate1(std::vector<int>::iterator first,
                 std::vector<int>::iterator last)
{
    int sum = std::accumulate(first, last, 0);      //标准库求和函数
    std::unique_lock<std::mutex> locker(mu);
    res = sum;
    locker.unlock();
    cond.notify_one();              // 向一个等待线程发出“条件已满足”的通知
}

int accumulate2(std::vector<int>::iterator first,
               std::vector<int>::iterator last)
{
    int sum = std::accumulate(first, last, 0);//求和的初始值为0
    return sum;
}



int main()
{
#if 0  //第一个线程异步方案
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::thread work_thread(accumulate1, numbers.begin(), numbers.end());//线程的定义   从这里开始运行

    std::unique_lock<std::mutex> locker(mu);
    //线程返回的值res是什么呢？res是一个全局变量，通过条件变量通知已经可以用了，表示锁已经释放了
    //等待的时候就会进行释放锁
    cond.wait(locker, [](){ return res;});   //如果条件变量被唤醒，检查结果是否被改变，为真则直接返回，为假则继续等待
    std::cout << "result=" << res << '\n';
//    work_thread.join();

//    locker.unlock();  //这个暂时看来没什么用
    work_thread.join();         //阻塞等待线程执行完成

    getchar();
#endif

    // 演示用 async 在线程间传递结果。
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    //调用方式：std::async(std::launch::async函数名字,需要异步执行的函数名字,参数1,参数2,...);通过get获得返回值进行操作
    auto accumulate_future = std::async(std::launch::async, accumulate2, numbers.begin(), numbers.end());        //auto可以自动推断变量的类型
    std::cout << "result=" << accumulate_future.get() << '\n';//通过get能够获得异步的返回值

    getchar();
    return 0;
}


