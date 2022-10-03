
//
// Created by sxh on 2022/10/3.
//
#ifndef DOUBLEPOINT_H
#define DOUBLEPOINT_H
#include <vector>
using namespace std;
//11.盛最多水的容器
/*
 *输入：[1,8,6,2,5,4,8,3,7]
 *输出：49
 *解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 * 思路：第一个和最后一个的高度最小值hmin，然后计算hmin*wight（两者的差值），这种穷举的方法会超过时间限制
 * 耗费时间：18298
 */
int maxArea(vector<int> &height);
int maxArea2(vector<int> &height);
int maxArea3(vector<int> &height);
int maxArea4(vector<int> &height);

//其他双指针的算法

int test(int a);
#endif

