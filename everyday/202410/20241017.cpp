/*
3193. 统计逆序对的数目

给你一个整数 n 和一个二维数组 requirements ，其中 requirements[i] = [endi, cnti] 表示这个要求中的末尾下标和 逆序对 的数目。

整数数组 nums 中一个下标对 (i, j) 如果满足以下条件，那么它们被称为一个 逆序对 ：

i < j 且 nums[i] > nums[j]

请你返回 [0, 1, 2, ..., n - 1] 的 排列 (排列是集合中所有元素的重新排序。) perm 的数目，满足对 所有 的 requirements[i] 都有 perm[0..endi] 恰好有 cnti 个逆序对。

由于答案可能会很大，将它对 109 + 7 取余 后返回。



示例 1：

输入：n = 3, requirements = [[2,2],[0,0]]

输出：2

解释：

两个排列为：

[2, 0, 1]
前缀 [2, 0, 1] 的逆序对为 (0, 1) 和 (0, 2) 。
前缀 [2] 的逆序对数目为 0 个。
[1, 2, 0]
前缀 [1, 2, 0] 的逆序对为 (0, 2) 和 (1, 2) 。
前缀 [1] 的逆序对数目为 0 个。



示例 2：

输入：n = 3, requirements = [[2,2],[1,1],[0,0]]

输出：1

解释：

唯一满足要求的排列是 [2, 0, 1] ：

前缀 [2, 0, 1] 的逆序对为 (0, 1) 和 (0, 2) 。
前缀 [2, 0] 的逆序对为 (0, 1) 。
前缀 [2] 的逆序对数目为 0 。



示例 3：

输入：n = 2, requirements = [[0,0],[1,0]]

输出：1

解释：

唯一满足要求的排列为 [0, 1] ：

前缀 [0] 的逆序对数目为 0 。
前缀 [0, 1] 的逆序对为 (0, 1) 。
 
 

提示：

2 <= n <= 300
1 <= requirements.length <= n
requirements[i] = [endi, cnti]
0 <= endi <= n - 1
0 <= cnti <= 400
输入保证至少有一个 i 满足 endi == n - 1 。
输入保证所有的 endi 互不相同。
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
  public:
    using ll = long long;
    ll mod = 1e9 + 7;
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        vector<int> cnt(n, -1);
        for (auto& it : requirements)
            cnt[it[0]] = it[1];//固定要求

        vector<vector<ll>> p(n, vector<ll>(cnt[n - 1] + 1, INT64_MIN));
        function<ll(int, int)> get = [&](int loc, int k) {//记忆化搜索
            if (k < 0)
                return 0LL;
            if (p[loc][k] != INT64_MIN)
                return p[loc][k];
            if (cnt[loc] != -1 && cnt[loc] != k)//不满足要求
                return p[loc][k] = 0;
            if (loc == 0)
                return p[loc][k] = k == 0 ? 1 : 0;
            p[loc][k] = 0;
            for (int i = 0; i <= loc; i++) {//枚举最后一位
                p[loc][k] += get(loc - 1, k - (loc - i));
                p[loc][k] %= mod;
            }
            return p[loc][k];
        };
        return (get(n - 1, cnt[n - 1]) + mod) % mod;
    }
};

int main() {
    Solution sol;
    int n = 3;
    vector<vector<int>> requirements = {{2, 2}, {0, 0}};
    cout << sol.numberOfPermutations(n, requirements) << endl;
    n = 3;
    requirements = {{2, 2}, {1, 1}, {0, 0}};
    cout << sol.numberOfPermutations(n, requirements) << endl;
    n = 2;
    requirements = {{0, 0}, {1, 0}};
    cout << sol.numberOfPermutations(n, requirements) << endl;
    return 0;
}