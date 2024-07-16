/*
2956. 找到两个数组中的公共元素

给你两个下标从 0 开始的整数数组 nums1 和 nums2 ，它们分别含有 n 和 m 个元素。请你计算以下两个数值：

answer1：使得 nums1[i] 在 nums2 中出现的下标 i 的数量。
answer2：使得 nums2[i] 在 nums1 中出现的下标 i 的数量。
返回 [answer1, answer2]。



示例 1：

输入：nums1 = [2,3,2], nums2 = [1,2]

输出：[2,1]

解释：

示例 2：

输入：nums1 = [4,3,2,3,1], nums2 = [2,2,5,2,3,6]

输出：[3,4]

解释：

nums1 中下标在 1，2，3 的元素在 nums2 中也存在。所以 answer1 为 3。

nums2 中下标在 0，1，3，4 的元素在 nums1 中也存在。所以 answer2 为 4。

示例 3：

输入：nums1 = [3,4,2,3], nums2 = [1,5]

输出：[0,0]

解释：

nums1 和 nums2 中没有相同的数字，所以答案是 [0,0]。

提示：

n == nums1.length
m == nums2.length
1 <= n, m <= 100
1 <= nums1[i], nums2[i] <= 100
*/
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        vector<pair<int, int>>cnt(101);
        int ans1 = 0, ans2 = 0;
        for (int v : nums1) cnt[v].first++;
        for (int v : nums2) {
            if (cnt[v].first) {
                // 第一个答案，如果第二个计数为0，说明v第一次在nums2出现，加上在nums1出现的次数；否则不是第一次出现，+0
                ans1 += cnt[v].second++ == 0 ? cnt[v].first : 0;
                // 重复的v在nums2出现一次+1
                ans2++;
            }
        }
        return { ans1,ans2 };
    }
};

int main() {
    Solution solution;
    for (auto [n1, n2] : vector<pair<vector<int>, vector<int>>>{
            {{2, 3, 2}, {1, 2}},
            {{4, 3, 2, 3, 1}, {2, 2, 5, 2, 3, 6}},
            {{3, 4, 2, 3}, {1, 5}}
        }) {
        auto result = solution.findIntersectionValues(n1, n2);
        cout << result[0] << " " << result[1] << endl;
    }
    return 0;
}
