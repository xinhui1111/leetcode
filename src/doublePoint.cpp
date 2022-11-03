//
// Created by sxh on 2022/10/3.
//

#include <algorithm>
#include <iostream>
#include "doublePoint.h"
int maxArea(vector<int> &height) {
    int hsize=height.size();
    //�ֱ�Ƚ�
    int h{0};
    int w{0};
    int Area{0};
    for(int i=0;i<hsize;++i){
        for(int j=i+1;j<hsize;++j){
            w=j-i;
            h=height[i]<height[j]?height[i]:height[j];
            if(Area<w*h){
                //�����ֵ��ͬʱ��Ҫ���λ��
                Area=w*h;
            }
        }
    }
    return Area;
}

//����һЩ���Ч�ʵķ�ʽ
/*
 * �ķ�ʱ�䣺20087
 */
int maxArea2(vector<int> &height) {
    int hsize=height.size();
    //�ֱ�Ƚ�
    int h{0};
    int w{0};
    int Area{0};
    for(int i=0;i<hsize;++i){
        for(int j=i+1;j<hsize;++j){
            if(height[i]>height[j] || height[hsize-1]>height[j]){
                //����
                continue;
            }
            w=j-i;
            h=height[i]<height[j]?height[i]:height[j];
            if(Area<w*h){
                //�����ֵ��ͬʱ��Ҫ���λ��
                Area=w*h;
            }
        }
    }
    return Area;
}


/*
 * �ķ�ʱ��25
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


//�ٷ��ⷨ��
/*
 * ˫ָ�������� ������Ϊ�����߽������λ�õķ�Χ����һ��ʼ��˫ָ��ָ����������ұ߽磬��ʾ ���������е�λ�ö�������Ϊ�����ı߽磬
 * ��Ϊ���ǻ�û�н��й��κγ��ԡ�����֮������ÿ�ν���Ӧ�����ֽ�С���Ǹ�ָ�� �� ��һ��ָ��ķ����ƶ�һ��λ�ã��ͱ�ʾ������Ϊ ���ָ�벻��������Ϊ�����ı߽��ˡ�
 * �ķ�ʱ���ǣ�40
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
 * �жϷ�����ʱ��ǰ�滹�Ǻ���
 */
bool front_back(int minute,int hour){
    if(minute>hour*5)//������ǰ��
        return true;
    else
        return false;
}

/*
 * ���������� hour �� minutes �����㷵����ʱ���ϣ��ɸ���ʱ���ʱ��ͷ�����ɵĽ�С�ǵĽǶȣ�60 ��λ�ƣ���
 * 360/12=30   15   180-15=165
 * 30/60=0.5 12*0.5=6     (6-12+12)mod 12=6��Ӧ��6*30=180   ƫ��30*0.5=15   �������180-15=165
 * ���룺hour = 12, minutes = 30
 * �����165
 */
double angleClock(int hour, int minutes) {
    //1.���������ʱ�ӵ������Ƕȣ��жϷ��ӻ���ʱ����ǰ���������������Ƿ�����ǰ
    bool flag= false;
    double angle{0.0};
    //�ж�ǰ��Ӧ����������λ�ý��бȽ�
    if(minutes > hour*5){//������ǰ��
        angle=minutes*6-(hour % 12)*30;
    }else
    {//ʱ����ǰ��
        flag= true;
        angle=-minutes*6+hour*30;
    }

    //2.����ƫ��
    double deviate{0.0};
    deviate=30*(minutes/60.0);
    if(!flag)
        angle=angle-deviate>0?(angle-deviate):(-angle+deviate);
    else
    {
        //ʱ����ǰ��,��ôƫ�Ƶ��ǲ��־��Ǽ���������ǰ����෴��ǰ����Ǽ�ȥ
        angle=angle+deviate;
    }

    //3.���⴦��
    //����360��ʱ����Ϊ���ᳬ������360�ȣ����Կ�����ô��
    if(angle>=360){
        angle-=360;
    }

    //Ҫ�����С���Ǹ��Ƕ�
    if(angle>180){
        angle=360-angle;
    }
    return angle;
};

int test(int a) {
    return a;
}

#if 0
/*
 * ����: nums = [0,1,0,3,12]
    ���: [1,3,12,0,0]
 */
void moveZeroes(vector<int> &nums) {
    //���ַ��������λ�ñ���
    //���Դ�ǰ��������ƣ�����0�ͽ��������󣬲��ҷ���֮��ָ������λ�þ���ǰ�ƶ�һλ
    int left{0};
    int right{static_cast<int>(nums.size()-1)};
    //ǰ������ָ�룬ǰ��һ��һ��������ƶ���������0�������Ľ���ת����ת����֮������ָ��ҲҪ��ǰ�ƶ�һ������0���������ƶ���
    while(left<right){
        if(nums[left]==0){
            //�����λ�ú����һ��λ�õ������л���
            if(nums[right]!=0){
                //���л���
                int temp{0};
                temp=nums[left];
                nums[left]=nums[right];
                nums[right]=temp;
            }
            right--;
        }
        left++;

    }
}
#endif

//0,1,0,3,12
//�ǳ�ˮ�ķ�������Ϊ���˺ܶ�ѭ��
void moveZeroes(vector<int> &nums) {
    int left{0};
    int right{static_cast<int>(nums.size()-1)};

    while (left<right){
        if(nums[left]==0){
            //�Ͱ�left�����ȫ����ǰ�ƶ�
            for(int i=left;i<right;i++){
                nums[i]=nums[i+1];
            }
            nums[right]=0;
            right--;
        }
        else
            left++;
    }

}

/*
 * ����˹ٷ��Ľⷨ
 * ��ָ��������ڵ�λ�ã����������0��ʱ�򣬾Ͱ�0����ǰ��
 */
void moveZeroes_Official(vector<int>& (nums)){
    int left{0};
    int right{0};
    while (right<nums.size()){
        if(nums[right]){
            //��left��right���л���
            int temp{0};
            temp=nums[left];
            nums[left]=nums[right];
            nums[right]=temp;

            left++;
        }
        right++;
    }
}


/*
 * ���룺nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * �����[1,2,2,3,5,6]
 * ���ͣ���Ҫ�ϲ� [1,2,3] �� [2,5,6] ��
 * �ϲ������ [1,2,2,3,5,6] ������б��Ӵֱ�ע��Ϊ nums1 �е�Ԫ�ء�
 *
 * �ⷨһ��ֱ�Ӻϲ�֮���������
 */
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int diff_len=nums1.size()-nums2.size();
    int nums2_len=nums2.size();
    for(int i=0;i<nums2_len;++i){
        nums1[diff_len+i]=nums2[i];
    }

    std::sort(nums1.begin(),nums1.end());
}

//1,2,3,0,0,0     2 5 6
void merge2(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    sort(nums1.begin(),nums1.end());
    sort(nums2.begin(),nums2.end());
    if(nums2.empty() || nums1.empty())
        return;
    vector<int>sorted(m+n,0);
    int left{0};
    int right{0};
    int pos{0};
    while(pos<m+n){
        //���ھ���Ҫ�������һ����������󣬺���һ��
        if(right>=n || nums1[left]<=nums2[right] && nums1[left]!=0){//ǰ��û�п��ǵ�0�����
            //��С�ڵķŽ�ȥ
            sorted[pos++]=nums1[left++];
            std::cout<<"pos:"<<pos<<"  "<<sorted[pos-1]<<"  left:"<<left<<"  right:"<<right<<"  pos:"<<pos<<endl;
        }
        else{
            //��С�ڵķŽ�ȥ
            sorted[pos++]=nums2[right++];
            std::cout<<"pos:"<<pos<<"  "<<sorted[pos-1]<<"  left:"<<left<<"  right:"<<right<<"  pos:"<<pos<<endl;
        }
    }

    for(int i=0;i<m+n;++i){
        nums1[i]= sorted[i];
    }
}

void merge3(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int p1 = 0, p2 = 0;
        int sorted[m + n];
        int cur;//��ߣ�sorted���ڵ�λ��
        while (p1 < m || p2 < n) {
            if (p1 == m) {
                cur = nums2[p2++];//�Ǳ߻�һֱ++
            } else if (p2 == n) {
                cur = nums1[p1++];//p1��һֱ++
            } else if (nums1[p1] < nums2[p2]) {
                cur = nums1[p1++];
            } else {
                cur = nums2[p2++];
            }
            sorted[p1 + p2 - 1] = cur;
        }
        for (int i = 0; i != m + n; ++i) {
            nums1[i] = sorted[i];
        }
    }

    /*
     * ���룺nums = [-1,0,1,2,-1,-4]
     * �����[[-1,-1,2],[-1,0,1]]
     * ���ͣ�
         * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 ��
         * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 ��
         * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 ��
         * ��ͬ����Ԫ���� [-1,0,1] �� [-1,-1,2] ��
         * ע�⣬�����˳�����Ԫ���˳�򲢲���Ҫ��
     */
vector<vector<int>> threeSum(vector<int> &nums) {
    //ʹ��left��right�ֱ�������ǰ������ƶ���������Ԫ�ؾͽ��й̶�
    //�Ƚ�������
    std::sort(nums.begin(),nums.end());
    for(auto tmp:nums){//��������֮��Ľ��
        cout<<tmp<<endl;
    }

    vector<vector<int>>result;

    int flag_0{1};
    bool first_flag= true;
    for(int i=0;i<nums.size() ;++i){
        if(nums[i]==0 ){//����Ϊ0�Ͳ��ᵽ���濼����
            flag_0++;
        }

        /*if(nums[i+1]==nums[i])
            continue;*/

        int left{i};
        int right{static_cast<int>(nums.size()-1)};
        while(left<right){
            //�̶�������Ԫ��ΪiԪ��
            if(left==i)
                left++;
            else if(right==i)
                right--;
            else{
                //��������Ԫ��
                if((nums[i]+nums[left]+nums[right])==0){
                    vector<int>tmp{nums[i],nums[left],nums[right]};
                    result.push_back(tmp);
                    while(nums[left++]==nums[left])
                    {

                    }

                    while(nums[right--]==nums[right])
                    {

                    }
                }
                else if((nums[i]+nums[left]+nums[right])>0){
                    while(nums[right--]==nums[right])
                    {

                    }
                }
                else
                {
                    while(nums[left++]==nums[left])
                    {

                    }
                }
            }
        }
        }

    if(flag_0>=3){
        vector<int>tmp{0,0,0};
        result.push_back(tmp);
    }
    return result;
}

//ʹ�ùٷ���˼·�Լ�����
/*
nums.sort()
for first = 0 .. n-1
    if first == 0 or nums[first] != nums[first-1] then
        // ������ѭ����Ӧ��ָ��
        third = n-1
        for second = first+1 .. n-1
            if second == first+1 or nums[second] != nums[second-1] then
                // �����ƶ�ָ�룬ֱ�� a+b+c ������ 0
                while nums[first]+nums[second]+nums[third] > 0
                    third = third-1
                // �ж��Ƿ��� a+b+c==0
                check(first, second, third)
                -4,-1,-1,0,1,2
 */
vector<vector<int>> threeSum2(vector<int> &nums) {
    std::sort(nums.begin(),nums.end());
    int n=nums.size();
    vector<vector<int>>result;
    for (int first = 0 ;first<=n-1;first++){
        //����֮����Ҫfirst����0�������ں���Ƚϵ���first-1�����û�д��ڳ�ʼֵ����ôfirst��Χ�ͻ᲻��
        //���ǵ�һ���϶���Ҫ�μӼ���ģ�Ҳ�������ظ������Ե�һ��ҲҪ���ǽ�ȥ��Ҳ����||������
        if( (first >0 && nums[first] != nums[first-1])||first==0){//TODO: ֮ǰ��first == 0��û�и������   ��Ҫ����0��Ϊ��first-1������
            // ������ѭ����Ӧ��ָ��
            int third = n-1;
            for(int second = first+1;second <=n-1;second++){

                if((second>first+1 && nums[second]!=nums[second-1])||(second==first+1)) {//TODO: ֮ǰ��second==first+1��û�и������
                    // �����ƶ�ָ�룬ֱ�� a+b+c ������ 0
                    while (nums[first] + nums[second] + nums[third] > 0 && third > second) {
                        cout << "����Ԫ��" << first << second <<third<< endl;
                        third = third - 1;

                    }

                    // �ж��Ƿ��� a+b+c==0
                    if (nums[first] + nums[second] + nums[third] == 0 && third > second) {
                        //�����б�;
                        result.push_back(vector<int>{nums[first], nums[second], nums[third]});
                        cout << nums[first] << "  " << nums[second] << "  " << nums[third] << endl;
                        continue;//TODO: ֮ǰ��ֱ��break����ѭ���ˣ���ô�ͼ��㲻�����еĽ��
                    }
                }
            }

        }
    }

    return result;
}
//TODO: дһ���������Ӷ�������



