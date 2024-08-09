/*
3132. 找出与数组相加的整数 II

给你两个整数数组 nums1 和 nums2。

从 nums1 中移除两个元素，并且所有其他元素都与变量 x 所表示的整数相加。如果 x 为负数，则表现为元素值的减少。

执行上述操作后，nums1 和 nums2 相等 。当两个数组中包含相同的整数，并且这些整数出现的频次相同时，两个数组 相等 。

返回能够实现数组相等的 最小 整数 x 。

 

示例 1:

输入：nums1 = [4,20,16,12,8], nums2 = [14,18,10]

输出：-2

解释：

移除 nums1 中下标为 [0,4] 的两个元素，并且每个元素与 -2 相加后，nums1 变为 [18,14,10] ，与 nums2 相等。



示例 2:

输入：nums1 = [3,5,5,3], nums2 = [7,7]

输出：2

解释：

移除 nums1 中下标为 [0,3] 的两个元素，并且每个元素与 2 相加后，nums1 变为 [7,7] ，与 nums2 相等。

 

提示：

3 <= nums1.length <= 200
nums2.length == nums1.length - 2
0 <= nums1[i], nums2[i] <= 1000
测试用例以这样的方式生成：存在一个整数 x，nums1 中的每个元素都与 x 相加后，再移除两个元素，nums1 可以与 nums2 相等。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumAddedInteger(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int n1=nums1.size(), n2=n1-2, ans=INT_MAX;
        for(int is=0;is<=2;is++){
            int diff=nums2[0]-nums1[is], cnt=0;
            for(int i=is,j=0;j<n2;i++,j++){
                while(i<n1 && nums2[j]-nums1[i]!=diff) 
                    i++;
                if(i==n1) break;
                cnt++;
            }
            if(cnt==n2) ans=min(ans, diff);
        }
        return ans;
    }
};

int main(){
    Solution* so = new Solution();
    vector<int> nums1 = {4,20,16,12,8};
    vector<int> nums2 = {14,18,10};
    int ans = so->minimumAddedInteger(nums1, nums2);
    cout<<ans<<endl;

    nums1 = {3,5,5,3};
    nums2 = {7,7};
    ans = so->minimumAddedInteger(nums1, nums2);
    cout<<ans<<endl;
    
    return 0;
}
