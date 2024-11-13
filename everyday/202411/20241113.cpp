/*
3261. 统计满足 K 约束的子字符串数量 II

给你一个 二进制 字符串 s 和一个整数 k。

另给你一个二维整数数组 queries ，其中 queries[i] = [li, ri] 。

如果一个 二进制字符串 满足以下任一条件，则认为该字符串满足 k 约束：

字符串中 0 的数量最多为 k。
字符串中 1 的数量最多为 k。

返回一个整数数组 answer ，其中 answer[i] 表示 s[li..ri] 中满足 k 约束 的 子字符串 的数量。

子字符串 是字符串中连续的 非空 字符序列。



示例 1：

输入：s = "0001111", k = 2, queries = [[0,6]]

输出：[26]

解释：

对于查询 [0, 6]， s[0..6] = "0001111" 的所有子字符串中，除 s[0..5] = "000111" 和 s[0..6] = "0001111" 外，其余子字符串都满足 k 约束。



示例 2：

输入：s = "010101", k = 1, queries = [[0,5],[1,4],[2,3]]

输出：[15,9,3]

解释：

s 的所有子字符串中，长度大于 3 的子字符串都不满足 k 约束。

 

提示：

1 <= s.length <= 105
s[i] 是 '0' 或 '1'
1 <= k <= s.length
1 <= queries.length <= 105
queries[i] == [li, ri]
0 <= li <= ri < s.length
所有查询互不相同
*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<long long> countKConstraintSubstrings(string s, int k, vector<vector<int>>& queries) {
        int cnt[2]{};
        int n = s.size();
        vector<int> d(n, n);  // 用一个数组 d 记录每个位置 i 右边第一个不满足 k 约束的位置，初始时 d[i]=n
        long long pre[n + 1]; // 用一个长度为 n+1 的前缀和数组 pre[i] 记录以前 i 个位置作为右边界的满足 k 约束的子字符串的个数
        pre[0] = 0;

        for (int i = 0, j = 0; j < n; ++j) {
            cnt[s[j] - '0']++;
            while (cnt[0] > k && cnt[1] > k) {
                d[i] = j;
                cnt[s[i++] - '0']--;
            }
            pre[j + 1] = pre[j] + j - i + 1;
        }

        vector<long long> ans;
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            int p = min(r + 1, d[l]);                  // 首先找出 l 右边第一个不满足 k 约束的位置 p
            long long a = (1LL + p - l) * (p - l) / 2; //  [l,p−1] 的所有子字符串都满足 k 约束
            long long b = pre[r + 1] - pre[p];         // 计算以 [p,r] 为右边界的满足 k 约束的子字符串的个数
            ans.push_back(a + b);
        }
        return ans;
    }
};

int main() {
    Solution sol;
    string s = "0001111";
    int k = 2;
    vector<vector<int>> queries{{0, 6}};
    vector<long long> ans = sol.countKConstraintSubstrings(s, k, queries);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;

    s = "010101";
    k = 1;
    queries = {{0, 5}, {1, 4}, {2, 3}};
    ans = sol.countKConstraintSubstrings(s, k, queries);
    for (auto x : ans) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}