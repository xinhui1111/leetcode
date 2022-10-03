//
// Created by sxh on 2022/10/3.
//
#include "doublePoint.h"
int maxArea(vector<int> &height) {
    int hsize=height.size();
    //分别比较
    int h{0};
    int w{0};
    int Area{0};
    for(int i=0;i<hsize;++i){
        for(int j=i+1;j<hsize;++j){
            w=j-i;
            h=height[i]<height[j]?height[i]:height[j];
            if(Area<w*h){
                //面积赋值，同时还要标记位置
                Area=w*h;
            }
        }
    }
    return Area;
}

//增加一些提高效率的方式
/*
 * 耗费时间：20087
 */
int maxArea2(vector<int> &height) {
    int hsize=height.size();
    //分别比较
    int h{0};
    int w{0};
    int Area{0};
    for(int i=0;i<hsize;++i){
        for(int j=i+1;j<hsize;++j){
            if(height[i]>height[j] || height[hsize-1]>height[j]){
                //跳过
                continue;
            }
            w=j-i;
            h=height[i]<height[j]?height[i]:height[j];
            if(Area<w*h){
                //面积赋值，同时还要标记位置
                Area=w*h;
            }
        }
    }
    return Area;
}


/*
 * 耗费时间25
 */
int maxArea3(vector<int> &height){
    int i = 0, j = height.size() - 1, res = 0;
    while(i < j) {
        res = height[i] < height[j] ?
              max(res, (j - i) * height[i++]):
              max(res, (j - i) * height[j--]);
    }
    return res;
}


//官方解法：
/*
 * 双指针代表的是 可以作为容器边界的所有位置的范围。在一开始，双指针指向数组的左右边界，表示 数组中所有的位置都可以作为容器的边界，
 * 因为我们还没有进行过任何尝试。在这之后，我们每次将对应的数字较小的那个指针 往 另一个指针的方向移动一个位置，就表示我们认为 这个指针不可能再作为容器的边界了。
 * 耗费时间是：40
 */
int maxArea4(vector<int> &height){
    int l = 0, r = height.size() - 1;
    int ans = 0;
    while (l < r) {
        int area = min(height[l], height[r]) * (r - l);
        ans = max(ans, area);
        if (height[l] <= height[r]) {
            ++l;
        }
        else {
            --r;
        }
    }
    return ans;
}

/*
 * 判断分钟在时钟前面还是后面
 */
bool front_back(int minute,int hour){
    if(minute>hour*5)//分钟在前面
        return true;
    else
        return false;
}

/*
 * 给你两个数 hour 和 minutes 。请你返回在时钟上，由给定时间的时针和分针组成的较小角的角度（60 单位制）。
 * 360/12=30   15   180-15=165
 * 30/60=0.5 12*0.5=6     (6-12+12)mod 12=6对应了6*30=180   偏离30*0.5=15   两个相减180-15=165
 * 输入：hour = 12, minutes = 30
 * 输出：165
 */
double angleClock(int hour, int minutes) {
    //1.计算分钟与时钟的整数角度，判断分钟还是时钟在前，现在这里计算的是分钟在前
    bool flag= false;
    double angle{0.0};
    //判断前后应该是与自身位置进行比较
    if(minutes > hour*5){//分钟在前面
        angle=minutes*6-(hour % 12)*30;
    }else
    {//时钟在前面
        flag= true;
        angle=-minutes*6+hour*30;
    }

    //2.计算偏离
    double deviate{0.0};
    deviate=30*(minutes/60.0);
    if(!flag)
        angle=angle-deviate>0?(angle-deviate):(-angle+deviate);
    else
    {
        //时钟在前面,那么偏移的那部分就是加上来，与前面的相反，前面的是减去
        angle=angle+deviate;
    }

    //3.特殊处理
    //超过360的时候，因为不会超过两个360度，所以可以这么算
    if(angle>=360){
        angle-=360;
    }

    //要计算出小的那个角度
    if(angle>180){
        angle=360-angle;
    }
    return angle;
};

int test(int a) {
    return a;
}

