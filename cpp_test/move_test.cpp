//
// Created by sxh on 2022/11/3.
//
/*
 * 参考：https://blog.csdn.net/CPriLuke/article/details/79462388
 * 简单来说，右值经过T&&传递类型保持不变还是右值，而左值经过T&&变为普通的左值引用.
 * 右值引用可以理解为不能更改的应用，比如变量的指针就是常量，它是不能够更改
 *
 * static_case:类似于C语言常用的强制类型转换 const_case:将const的变量、去掉const属性,但必须是指针或引用作为左值
 *
 *
 * 参考：https://zhuanlan.zhihu.com/p/94588204
 * 右值引用(&&)，移动构造函数，移动复制运算符以及std::move
 *
 * 移动构造函数（两个引用）
    Integer(Integer&& source)
	  : m_ptr(source.m_ptr) {
	    source.m_ptr= nullptr;
	    cout << "Call Integer(Integer&& source)移动" << endl;
	}
 可以看到如果传入的是这个，那么之前的指针就会被释放为空，而本身就会被构造成原本的值

 使用场景：
    1 定义的类使用了资源并定义了移动构造函数和移动赋值运算符；
    2 该变量即将不再使用；
 */
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


int main()
{
    double d = 1;
    void* p = &d;
    double *dp = static_cast<double*>( p); //正确
    cout<<*dp<<endl;

    const char *cp = "hello";
//    char *q = static_cast<char*>(cp); //错误：static不能去掉const性质
    string cp_str=static_cast<string>(cp); //正确
    cout<<cp_str<<endl;

    /*
     * 移除引用
    template<typename T>
    class remove_reference<T&> //传入的是引用，而到了public那里就是T了
    {
    public:
       typedef T type;
    };
     */
    //参考：https://blog.csdn.net/slslslyxz/article/details/105778734
    //移除引用(*a的类型实际上是int& ，所以此时修改a[0] 等同于修改了b)
    //*a的类型是int，decltype（*a）之所以是int &,是因为*a是左值，它推导出来为 int &
    //*ptr 本身就是可以修改和读取一个内存中的值，这就是个引用
    int a[] = {1,2,3};
    std::remove_reference<decltype(*a)>::type b = a[0];
    a[0] = 4;
    cout << b; //输出1
    return 0;
}
