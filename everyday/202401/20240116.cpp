/*
2719. 统计整数数目

给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数：

num1 <= x <= num2
min_sum <= digit_sum(x) <= max_sum.
请你返回好整数的数目。答案可能很大，请返回答案对 109 + 7 取余后的结果。

注意，digit_sum(x) 表示 x 各位数字之和。

示例 1：

输入：num1 = "1", num2 = "12", min_num = 1, max_num = 8
输出：11
解释：总共有 11 个整数的数位和在 1 到 8 之间，分别是 1,2,3,4,5,6,7,8,10,11 和 12 。所以我们返回 11 。

示例 2：

输入：num1 = "1", num2 = "5", min_num = 1, max_num = 5
输出：5
解释：数位和在 1 到 5 之间的 5 个整数分别为 1,2,3,4 和 5 。所以我们返回 5 。


提示：

1 <= num1 <= num2 <= 10^22
1 <= min_sum <= max_sum <= 400
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
    int cal(string& s, int min_sum, int max_sum) {
        int n = s.length();
        vector<vector<int>> v(n, vector<int>(min(9 * n, max_sum) + 1, -1));

        function<int(int, int, bool)> dfs = [&](int pos, int sum, bool up_limit) -> int {
            if (sum > max_sum) return 0; // 和 超上界
            if (pos == n) return sum >= min_sum ? 1 : 0; // 和 没超下届，超过下届
            if (!up_limit && v[pos][sum] != -1) return v[pos][sum]; // 当前数值未到上限，并且有值

            int up = up_limit ? s[pos] - '0' : 9;
            int res = 0;
            for (int d = 0; d <= up; d++) res = (res + dfs(pos + 1, sum + d, up_limit && d == up)) % MOD;

            if (!up_limit) v[pos][sum] = res;
            return res;
            };

        return dfs(0, 0, true);
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum) {

        // 判断num1合法否？
        int sum = 0;
        for (char c : num1) sum += c - '0';
        int num1Legal = min_sum <= sum && sum <= max_sum;

        // 整体思路：计算 ≤num2 的好整数个数，记作 a；计算 ≤num1 的好整数个数，记作 b；总的 a-b+num1Legal，+MOD避免负数
        return (cal(num2, min_sum, max_sum) - cal(num1, min_sum, max_sum) + MOD + num1Legal) % MOD;
    }
};

int main() {
    Solution s;
    cout << s.count("1", "12", 1, 8) << endl;
    cout << s.count("1", "5", 1, 5) << endl;
    return 0;
}