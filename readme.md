# 说明
## 原本leetcode刷题的文件夹
主要关注两个文件，因为这两个函数里面是有主函数的
1. main.cpp：主要运行的是leetcode里面的程序；
   - doublePoint.cpp是双指针的程序
   - MutliThread.cpp是多线程的程序
   - time_chrono_signal_test.cpp是时间相关的程序
   - copy.cpp测试深拷贝和浅拷贝
   - 
2. test.cpp：运行的是测试程序；
    - 平时有时候功能看不懂就在这个文件里进行测试

# 新文件夹的增加
cpp_test
1. cpp_test/move_test.cpp 
   - 实现了std::move以及说明了其对应的场景
   - std::move中使用了remove_reference和static_case强制转换，remove_reference是`能够将X& &、X&& &、X& &&都折叠成X&， 用于处理左值`和`X&& &&折叠成X&&， 用于处理右值`
