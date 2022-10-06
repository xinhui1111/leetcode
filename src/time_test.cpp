//
// Created by sxh on 2022/10/5.
//

//chrono时间库的函数使用

#include <iostream>
#include <chrono>
#include <unistd.h>//pause函数导入头文件
#include <csignal>

using std::cout;
using std::endl;

/*
 * 使用信号的流程：
 * 1.首先使用signal函数提前注册一个中断函数，该函数用于将函数指针和信号做一个绑定;
 * 2.当程序进行执行pause，该进程暂停，等待处理信号。如果和signal中注册的信号相同，将会执行siganl中注册的函数，
 *   再继续执行后续代码；如果不同，将不会执行绑定的操作，直接退出。
 */


/*
 * 使用时间库的流程以及时间库的结构
 */

int main()
{
    signal(SIGINT,[](int sig){cout << "结束了该进程   over pause" << endl;});//注册了一个信号，将函数指针与信号绑定在一起
    std::chrono::milliseconds mscond(1000); // 1 second
    std::cout << mscond.count() << " milliseconds.\n";

    std::cout << mscond.count() * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den;
    std::cout << " seconds.\n";
    //system("pause");//windows下的暂停函数
    //linux下的暂停函数
    pause();
    return 0;
}