/*
1338. 数组大小减半

给你一个整数数组 arr。你可以从中选出一个整数集合，并删除这些整数在数组中的每次出现。

返回 至少 能删除数组中的一半整数的整数集合的最小大小。


示例 1：

输入：arr = [3,3,3,3,5,5,5,2,2,7]
输出：2
解释：选择 {3,7} 使得结果数组为 [5,5,5,2,2]、长度为 5（原数组长度的一半）。
大小为 2 的可行集合有 {3,5},{3,2},{5,2}。
选择 {2,7} 是不可行的，它的结果数组为 [3,3,3,3,5,5,5]，新数组长度大于原数组的二分之一。


示例 2：

输入：arr = [7,7,7,7,7,7]
输出：1
解释：我们只能选择集合 {7}，结果数组为空。
 

提示：

1 <= arr.length <= 105
arr.length 为偶数
1 <= arr[i] <= 105
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size(), sum = 0, ans = 0;
        vector<int> help(100000 , 0);
        for(int i = 0; i < n; i++) help[arr[i] - 1]++;
        sort(help.begin(), help.end());
        
        for(int i = 99999; i >= 0; i--) {
            if(help[i]) {
                //cout << i <<" ";
                sum += help[i];
                ans++;
                if(sum >= n / 2) break;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> arr = {3,3,3,3,5,5,5,2,2,7};
    cout << s.minSetSize(arr) << endl;
    arr = {7,7,7,7,7,7};
    cout << s.minSetSize(arr) << endl;
    return 0;
}