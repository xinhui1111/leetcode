
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
/*
 * 给你两个数 hour 和 minutes 。请你返回在时钟上，由给定时间的时针和分针组成的较小角的角度（60 单位制）。
 * 360/12=30   15   180-15=165
 * 30/60=0.5 12*0.5=6     (6-12+12)mod 12=6对应了6*30=180   偏离30*0.5=15   两个相减180-15=165
 * 输入：hour = 12, minutes = 30
 * 输出：165
 */
bool front_back(int minute,int hour);//判断分钟在时钟前面还是后面
double angleClock(int hour, int minutes);


/*
 * 283 移动零
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
 */
void moveZeroes(vector<int>& nums) ;

//官方解法
void moveZeroes_Official(vector<int>& (nums));

/*
 * 给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。
 * 请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。
 *
 */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
//非递减合并排序：使用双指针法进行解,一直出错
void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n);
//非递减合并排序：官方解法
void merge3(vector<int>& nums1, int m, vector<int>& nums2, int n);

int test(int a);
#endif

