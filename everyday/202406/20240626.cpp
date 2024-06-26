/*
2741. 特别的排列

给你一个下标从 0 开始的整数数组 nums ，它包含 n 个 互不相同 的正整数。如果 nums 的一个排列满足以下条件，我们称它是一个特别的排列：

对于 0 <= i < n - 1 的下标 i ，要么 nums[i] % nums[i+1] == 0 ，要么 nums[i+1] % nums[i] == 0 。

请你返回特别排列的总数目，由于答案可能很大，请将它对 109 + 7 取余 后返回。

示例 1：

输入：nums = [2,3,6]
输出：2
解释：[3,6,2] 和 [2,6,3] 是 nums 两个特别的排列。

示例 2：

输入：nums = [1,4,3]
输出：2
解释：[3,1,4] 和 [4,1,3] 是 nums 两个特别的排列。

示例 3：

输入：nums = [135146363,405439089,810878178,270292726,24572066,196576528,589729584]
输出：24

提示：

2 <= nums.length <= 14
1 <= nums[i] <= 109
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size(), m = (1 << n) - 1;
        vector<vector<long long>> memo(m, vector<long long>(n, -1)); // -1 表示没有计算过

        // msk 表示可以选择的下标集合，i 表示前一个下标
        function<long long(int, int)> dfs = [&](int msk, int i) -> long long {
            if (msk == 0) return 1;    // 找到一个特别排列

            auto& res = memo[msk][i];  // 注意这里是引用
            if (res != -1) return res; // 之前计算过
            res = 0;

            // 当前下标 j
            for (int j = 0; j < n; j++) {
                // (msk >> j & 1) 表示可选该下标，后面是 特别排列 的条件
                if ((msk >> j & 1) && ((nums[i] % nums[j] == 0) || (nums[j] % nums[i] == 0))) {
                    res += dfs(msk ^ (1 << j), j);
                }
            }
            return res;
            };

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += dfs(m ^ (1 << i), i);
        }
        return ans % 1000000007;
    }
};

int main() {
    Solution sol;
    for (auto& nums : vector<vector<int>>{ {2,3,6}, {1,4,3}, {135146363,405439089,810878178,270292726,24572066,196576528,589729584} }) {
        cout << sol.specialPerm(nums) << endl;
    }
    return 0;
}