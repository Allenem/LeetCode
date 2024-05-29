/*
2865. 美丽塔 I

给你一个长度为 n 下标从 0 开始的整数数组 maxHeights 。

你的任务是在坐标轴上建 n 座塔。第 i 座塔的下标为 i ，高度为 heights[i] 。

如果以下条件满足，我们称这些塔是 美丽 的：

1 <= heights[i] <= maxHeights[i]
heights 是一个 山脉 数组。
如果存在下标 i 满足以下条件，那么我们称数组 heights 是一个 山脉 数组：

对于所有 0 < j <= i ，都有 heights[j - 1] <= heights[j]
对于所有 i <= k < n - 1 ，都有 heights[k + 1] <= heights[k]
请你返回满足 美丽塔 要求的方案中，高度和的最大值 。

示例 1：

输入：maxHeights = [5,3,4,1,1]
输出：13
解释：和最大的美丽塔方案为 heights = [5,3,3,1,1] ，这是一个美丽塔方案，因为：
- 1 <= heights[i] <= maxHeights[i]
- heights 是个山脉数组，峰值在 i = 0 处。
13 是所有美丽塔方案中的最大高度和。

示例 2：

输入：maxHeights = [6,5,3,9,2,7]
输出：22
解释： 和最大的美丽塔方案为 heights = [3,3,3,9,2,2] ，这是一个美丽塔方案，因为：
- 1 <= heights[i] <= maxHeights[i]
- heights 是个山脉数组，峰值在 i = 3 处。
22 是所有美丽塔方案中的最大高度和。

示例 3：

输入：maxHeights = [3,2,5,5,2,3]
输出：18
解释：和最大的美丽塔方案为 heights = [2,2,5,5,2,2] ，这是一个美丽塔方案，因为：
- 1 <= heights[i] <= maxHeights[i]
- heights 是个山脉数组，最大值在 i = 2 处。
注意，在这个方案中，i = 3 也是一个峰值。
18 是所有美丽塔方案中的最大高度和。

提示：

1 <= n == maxHeights <= 103
1 <= maxHeights[i] <= 109
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    long long maximumSumOfHeights(vector<int>& maxHeights) {
        using ll = long long;
        int n = maxHeights.size();

        vector<ll> suf(n + 1); // 後綴和, n+1 是為了與 前綴和 相加時下標 i+1 存在
        stack<int> st; // 這裡是後綴和 下標 的單調棧，從n-1到i單調遞增
        st.push(n); // 哨兵
        ll sum = 0;

        for (int i = n - 1; i > -1; --i) {
            int x = maxHeights[i];
            while (st.size() > 1 && x <= maxHeights[st.top()]) { // 保持當前 maxHeights[i] 最大
                int j = st.top();
                st.pop();
                sum -= (ll)maxHeights[j] * (st.top() - j); // 撤销之前加到 sum 中的
            }
            sum += (ll)x * (st.top() - i); // 从 i 到 st.top()-1 都是 x，即把之前撤銷的都設置為 x
            suf[i] = sum;
            st.push(i);
        }

        ll ans = sum;
        st = stack<int>(); // 這裡是前綴和 下標 的單調棧，從0到i單調遞增
        st.push(-1); // 哨兵
        ll pre = 0; // 這裡不用 vector<ll> 是因為可以每一步直接使用，不用暫存到 vector 中
        for (int i = 0; i < n; ++i) {
            int x = maxHeights[i];
            while (st.size() > 1 && x <= maxHeights[st.top()]) {
                int j = st.top();
                st.pop();
                pre -= (ll)maxHeights[j] * (j - st.top()); // 撤销之前加到 pre 中的
            }
            pre += (ll)x * (i - st.top()); // 从 st.top()+1 到 i 都是 x
            ans = max(ans, pre + suf[i + 1]);
            st.push(i);
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> maxHeights = { 5,3,4,1,1 };
    cout << sol.maximumSumOfHeights(maxHeights) << endl;

    maxHeights = { 6,5,3,9,2,7 };
    cout << sol.maximumSumOfHeights(maxHeights) << endl;

    maxHeights = { 3,2,5,5,2,3 };
    cout << sol.maximumSumOfHeights(maxHeights) << endl;

    return 0;
}