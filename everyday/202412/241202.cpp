/*
52. N 皇后 II

n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。

 

示例 1：


输入：n = 4
输出：2
解释：如上图所示，4 皇后问题存在两个不同的解法。


示例 2：

输入：n = 1
输出：1
 

提示：

1 <= n <= 9
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        int ans = 0;
        vector<int> col(n), diag1(n * 2 - 1), diag2(n * 2 - 1);
        auto dfs = [&](auto&& dfs, int r) {
            if (r == n) {
                ans++; // 找到一个合法方案
                return;
            }
            for (int c = 0; c < n; c++) {
                int rc = r - c + n - 1;
                if (!col[c] && !diag1[r + c] && !diag2[rc]) {
                    col[c] = diag1[r + c] = diag2[rc] = true;
                    dfs(dfs, r + 1);
                    col[c] = diag1[r + c] = diag2[rc] = false; // 恢复现场
                }
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};

int main() {
    Solution s;
    cout << s.totalNQueens(4) << endl;
    cout << s.totalNQueens(1) << endl;
    return 0;
}