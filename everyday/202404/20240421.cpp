/*
216. 组合总和 III

找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：

只使用数字1到9
每个数字 最多使用一次
返回 所有可能的有效组合的列表
。该列表不能包含相同的组合两次，组合可以以任何顺序返回。

示例 1:

输入: k = 3, n = 7
输出: [[1,2,4]]
解释:
1 + 2 + 4 = 7
没有其他符合的组合了。

示例 2:

输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
解释:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
没有其他符合的组合了。

示例 3:

输入: k = 4, n = 1
输出: []
解释: 不存在有效的组合。
在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 >
1，没有有效的组合。

提示:

2 <= k <= 9
1 <= n <= 60
*/

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> used(10), tmp;
        vector<vector<int>> ret;

        function<void(int, int, vector<int>)> dfs = [&](int idx, int rest,
                                                        vector<int> pre) {
            if (pre.size() == k && rest == 0) {
                ret.push_back(pre);
                return;
            }
            if (pre.size() < k) {
                for (int i = idx; i < 10; ++i) {
                    if (!used[i] && i <= rest) {
                        pre.push_back(i);
                        used[i] = 1;
                        dfs(i + 1, rest - i, pre);
                        pre.pop_back();
                        used[i] = 0;
                    }
                }
            }
        };

        dfs(1, n, tmp);
        return ret;
    }
};

int main() {
    Solution s;
    vector<vector<int>> ret = s.combinationSum3(3, 7);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    ret = s.combinationSum3(3, 9);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    ret = s.combinationSum3(4, 1);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}