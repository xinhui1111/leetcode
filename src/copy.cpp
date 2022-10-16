//
// Created by sxh on 2022/10/10.
//实现深拷贝和浅拷贝的区别
//
#include <iostream>

#if 0
class A
{
public:
    A(int _data) : data(_data){}
    void print(){
        std::cout<<"data:"<<data<<"  &data:"<<&data<<"\n";
    }
private:
    int data;
};

int main()
{
    A a(5), b = a; // 仅仅是数据成员之间的赋值
    b.print();
    a.print();
}
#endif

/*
 * 参考：https://blog.csdn.net/u014183456/article/details/117380821?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-117380821-blog-114088993.pc_relevant_3mothn_strategy_and_data_recovery&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-117380821-blog-114088993.pc_relevant_3mothn_strategy_and_data_recovery&utm_relevant_index=2
 * 有堆，文件，系统资源这些的时候，深拷贝就需要注意了
 */
class A
{
public:
    A(int _size) : size(_size)
    {
        data = new int[size];
    } // 假如其中有一段动态分配的内存

    A(const A& a){
        this->data=new int[a.size];
        for(int i=0;i<a.size;++i){
            this->data[i]=a.data[i];
        }
    }

    A& operator=(const A &a){
        //实现重载运算符
        if(this!=&a){
//            this->data=a.data;
            //申请空间并拷贝内容
            this->data=new int[a.size];
            for(int i=0;i<a.size;++i){
                this->data[i]=a.data[i];
            }

        }
    }
    ~A()
    {
        delete [] data;
    } // 析构时释放资源

    //打印变量值
    void print(){
        for(int i=0;i<size;++i){
            std::cout<<data[i]<<std::endl;
        }
    }
private:
    int* data;
    int size;
};

int main_copy()
{
    A a(5), b = a;
    a.print();
}



