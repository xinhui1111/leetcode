//
// Created by sxh on 2022/10/4.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

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

int main1() {
    // 函数的例子
    std::cout << "function example:\n";
    std::thread t1(fun, 100000);
    std::thread t2(fun, 100000);
    t1.join();
    t2.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 类的例子
    std::cout << "\nclass example:\n";
    C c;
    c._N = 0;
    std::thread t3(&C::fun, &c, 100000);
    std::thread t4(&C::fun, &c, 100000);
    t3.join();
    t4.join();

    return 0;
}


