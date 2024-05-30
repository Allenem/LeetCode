/*
2982. 找出出现至少三次的最长特殊子字符串 II

给你一个仅由小写英文字母组成的字符串 s 。

如果一个字符串仅由单一字符组成，那么它被称为 特殊 字符串。例如，字符串 "abc" 不是特殊字符串，而字符串 "ddd"、"zz" 和 "f" 是特殊字符串。

返回在 s 中出现 至少三次 的 最长特殊子字符串 的长度，如果不存在出现至少三次的特殊子字符串，则返回 -1 。

子字符串 是字符串中的一个连续 非空 字符序列。

示例 1：

输入：s = "aaaa"
输出：2
解释：出现三次的最长特殊子字符串是 "aa" ：子字符串 "aaaa"、"aaaa" 和 "aaaa"。
可以证明最大长度是 2 。

示例 2：

输入：s = "abcdef"
输出：-1
解释：不存在出现至少三次的特殊子字符串。因此返回 -1 。

示例 3：

输入：s = "abcaba"
输出：1
解释：出现三次的最长特殊子字符串是 "a" ：子字符串 "abcaba"、"abcaba" 和 "abcaba"。
可以证明最大长度是 1 。

提示：

3 <= s.length <= 50 * 10^5
s 仅由小写英文字母组成。
*/
#include <algorithm>
#include <functional>
#include <ranges>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maximumLength(string s) {
        vector<int> groups[26];
        int cnt = 0, n = s.length();
        for (int i = 0; i < n; i++) {
            cnt++;
            if (i + 1 == n || s[i] != s[i + 1]) {
                groups[s[i] - 'a'].push_back(cnt); // 统计连续字符长度
                cnt = 0;
            }
        }

        int ans = 0;
        for (auto& a : groups) {
            if (a.empty()) continue;
            ranges::sort(a, greater()); // 降序排序
            a.push_back(0);
            a.push_back(0); // 假设还有两个空串
            // 第一种情况：最长特殊子字符串长度 - 2，3次
            // 第二种情况：a[0] == a[1]，a[0] - 1 == a[1] - 1 可以出现4次；a[0] > a[1]，a[0]里面a[1]，2次，a[1]，1次；
            // 第三种情况：a[2]，3次
            ans = max({ ans, a[0] - 2, min(a[0] - 1, a[1]), a[2] });
        }

        return ans ? ans : -1;
    }
};

int main() {
    Solution sol;
    cout << sol.maximumLength("aaaa") << endl; // 2
    cout << sol.maximumLength("abcdef") << endl; // -1
    cout << sol.maximumLength("abcaba") << endl; // 1
    return 0;
}
// g++ 20240529.cpp -std=c++20