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

int test(int a) {
    return a;
}

