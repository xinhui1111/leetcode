//
// Created by sxh on 2022/10/4.
//

#ifndef HELLO_HEADERS_MUTLITHREAD_H
#define HELLO_HEADERS_MUTLITHREAD_H
#include <functional>
#include <thread>
#include <iostream>

using namespace std;

/*
 * 1116
 * 现有函数 printNumber 可以用一个整数参数调用，并输出该整数到控制台。
 * 例如，调用 printNumber(7) 将会输出 7 到控制台。
 *
 * 给你类 ZeroEvenOdd 的一个实例，该类中有三个函数：zero、even 和 odd 。ZeroEvenOdd 的相同实例将会传递给三个不同线程：
 * 线程 A：调用 zero() ，只输出 0
 * 线程 B：调用 even() ，只输出偶数
 * 线程 C：调用 odd() ，只输出奇数
 * 修改给出的类，以输出序列 "010203040506..." ，其中序列的长度必须为 2n 。
 *
 * 实现 ZeroEvenOdd 类：
 * ZeroEvenOdd(int n) 用数字 n 初始化对象，表示需要输出的数。
 * void zero(printNumber) 调用 printNumber 以输出一个 0 。
 * void even(printNumber) 调用printNumber 以输出偶数。
 * void odd(printNumber) 调用 printNumber 以输出奇数。
 */
class ZeroEvenOdd {
public:
    void test(int n);
    ZeroEvenOdd(){}
    ~ZeroEvenOdd(){}
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
     void zero(function<void(int)> printNumber) {
        cout<<"zero:"<<n<<"   flag:"<<flag<<endl;
        for (int i = 1; i <= n; ++i) {
            while (flag != 0) {
                /*cout<<"yield"<<endl;*/
                this_thread::yield();//std::this_thread::yield(); 是将当前线程所抢到的CPU”时间片A”让渡给其他线程(其他线程会争抢”时间片A”,
            }
            printNumber(0);
            if (i % 2 == 0) {
                flag = 2;
            } else {
                flag = 1;
            }
        }
    }

     void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i += 2) {
            while (flag != 2) {
                this_thread::yield();
            }
            printNumber(i);
            flag = 0;
        }
    }

     void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i += 2) {
            while (flag != 1) {
                this_thread::yield();
            }
            printNumber(i);
            flag = 0;
        }
    }

private:
    int n;
    int flag=1;//flag看应该初始化多少
};



#endif //HELLO_HEADERS_MUTLITHREAD_H
