//
// Created by sxh on 2022/10/5.
//

//chrono时间库的函数使用
//从系统获得的时间一般默认就是以秒来进行表示的

#include <iostream>
#include <chrono>
#include <unistd.h>//pause函数导入头文件
#include <csignal>
#include <thread>

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
Clocks
    system_clock           本地系统的当前时间 (可以调整)——就相当于电脑右下角的时间
    steady_clock           不能被调整的，稳定增加的时间
    high_resolution_clock  提供最高精度的计时周期，在不同的标准库中，high_resolution_clock 的实现不一致，推荐前面两种
Duration
    duration  时间段
Time point
    time_point  时间点
 */

/*
 *
时间段的单位定义：
    typedef duration <Rep, ratio<3600,1>> hours;   //在使用的时候直接使用std::chrono::milliseconds
    typedef duration <Rep, ratio<60,1>> minutes;
    typedef duration <Rep, ratio<1,1>> seconds;
    typedef duration <Rep, ratio<1,1000>> milliseconds;
    typedef duration <Rep, ratio<1,1000000>> microseconds;
    typedef duration <Rep, ratio<1,1000000000>> nanoseconds;
 */

using std::chrono::time_point;
void time_elapsed(){
    // "start" and "end"'s type is std::chrono::time_point
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));//使用了休眠时间为秒
    }
    time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();

    std::cout<<"将时间转换为毫秒\n"<<endl;
    //从这里可以看出直接的std::chrono::duration<double> elapsed是默认的秒，需要指定了之后才是毫秒或者其他想要指定的
    std::chrono::milliseconds elapsed1=std::chrono::duration_cast<std::chrono::milliseconds>(end - start);//将秒转换为毫秒
    std::chrono::duration<double> elapsed =  end - start;
//    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"elapsed: "<<elapsed1.count()<<endl;
    std::cout << "Elapsed time: " << elapsed.count() << "s\n";
}

void time_convert(){
    using namespace std::chrono;
    typedef duration<int,std::ratio<60*60*24>> days_type;
    time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());//时钟记录的是秒表示的，所以转换到一天的话就是60*60*24
    std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
}

__attribute__((unused)) int main_time_chrono_signal_test()//__attribute__((unused))编译器忽略该函数没有被使用的报警
{
    cout<<"=========================\n";
    time_elapsed();
    cout<<"=========================\n";

    signal(SIGINT,[](int sig){cout << "结束了该进程   over pause" << endl;});//注册了一个信号，将函数指针与信号绑定在一起
    std::chrono::milliseconds mscond(1000); // 1 second
    std::cout << mscond.count() << " milliseconds.\n";

    /*
     * Num代表分子，Denom代表分母
     */
    std::cout << mscond.count() * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den;
    std::cout << " seconds.\n";
    //system("pause");//windows下的暂停函数
    //linux下的暂停函数
    //pause();
    return 0;
}