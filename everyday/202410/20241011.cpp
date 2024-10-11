/*
3164. 优质数对的总数 II

给你两个整数数组 nums1 和 nums2，长度分别为 n 和 m。同时给你一个正整数 k。

如果 nums1[i] 可以被 nums2[j] * k 整除，则称数对 (i, j) 为 优质数对（0 <= i <= n - 1, 0 <= j <= m - 1）。

返回 优质数对 的总数。


示例 1：

输入：nums1 = [1,3,4], nums2 = [1,3,4], k = 1

输出：5

解释：

5个优质数对分别是 (0, 0), (1, 0), (1, 1), (2, 0), 和 (2, 2)。


示例 2：

输入：nums1 = [1,2,4,12], nums2 = [2,4], k = 3

输出：2

解释：

2个优质数对分别是 (3, 0) 和 (3, 1)。


提示：

1 <= n, m <= 105
1 <= nums1[i], nums2[j] <= 106
1 <= k <= 103
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> count1, count2;
        int max1 = 0;
        for (int num : nums1) {
            count1[num]++;
            max1 = max(max1, num);
        }
        for (int num : nums2) {
            count2[num]++;
        }
        long long res = 0;
        for (const auto& pair : count2) {
            int a = pair.first, cnt = pair.second;
            for (int b = a * k; b <= max1; b += a * k) {
                if (count1.count(b) > 0) {
                    res += 1L * count1[b] * cnt;
                }
            }
        }
        return res;

    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1,3,4}, nums2 = {1,3,4};
    int k = 1;
    cout << sol.numberOfPairs(nums1, nums2, k) << endl;

    nums1 = {1,2,4,12}, nums2 = {2,4};
    k = 3;
    cout << sol.numberOfPairs(nums1, nums2, k) << endl;
    
    return 0;
}