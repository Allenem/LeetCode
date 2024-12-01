/*
51. N 皇后

按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。



示例 1：

输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。



示例 2：

输入：n = 1
输出：[["Q"]]
 

提示：

1 <= n <= 9
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<int> queens;
        vector<int> xy_dif;
        vector<int> xy_sum;
        DFS(n, queens, xy_dif, xy_sum, result);
        return result;
    }

private:
    void DFS(int n, vector<int>& queens, vector<int>& xy_dif, vector<int>& xy_sum, vector<vector<string>>& result) {
        // 如果已经放置了 n 个皇后，说明找到了一种解决方案
        if (queens.size() == n) {
            vector<string> solution;
            // 将当前皇后的位置转换为棋盘表示
            for (int i : queens) {
                string row(n, '.'); // 创建一个长度为 n 的字符串，初始全部为 '.'
                row[i] = 'Q'; // 在皇后的位置放置 'Q'
                solution.push_back(row); // 将这一行加入到解决方案中
            }
            result.push_back(solution); // 将当前解决方案加入结果集中
            return;
        }
        // 尝试在当前行的每一列放置皇后
        for (int i = 0; i < n; ++i) {
            // 检查当前列和两个对角线是否已经有皇后
            if (find(queens.begin(), queens.end(), i) == queens.end() &&
                find(xy_dif.begin(), xy_dif.end(), queens.size() - i) == xy_dif.end() &&
                find(xy_sum.begin(), xy_sum.end(), queens.size() + i) == xy_sum.end()) {
                // 如果当前位置合法，放置皇后并更新状态
                queens.push_back(i);
                xy_dif.push_back(queens.size() - 1 - i);
                xy_sum.push_back(queens.size() - 1 + i);
                // 递归调用 DFS 处理下一行
                DFS(n, queens, xy_dif, xy_sum, result);
                // 回溯：移除皇后并恢复状态
                queens.pop_back();
                xy_dif.pop_back();
                xy_sum.pop_back();
            }
        }
    }
};

int main() {
    Solution sol;
    int n = 4;
    vector<vector<string>> result = sol.solveNQueens(n);
    for (const auto& solution : result) {
        for (const auto& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }

    n = 1;
    result = sol.solveNQueens(n);
    for (const auto& solution : result) {
        for (const auto& row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }
    
    return 0;
}