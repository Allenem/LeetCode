/*
2617. 网格图中最少访问的格子数

给你一个下标从 0 开始的 m x n 整数矩阵 grid 。你一开始的位置在 左上角 格子 (0,
0) 。

当你在格子 (i, j) 的时候，你可以移动到以下格子之一：

满足 j < k <= grid[i][j] + j 的格子 (i, k) （向右移动），或者
满足 i < k <= grid[i][j] + i 的格子 (k, j) （向下移动）。
请你返回到达 右下角 格子 (m - 1, n - 1)
需要经过的最少移动格子数，如果无法到达右下角格子，请你返回 -1 。

示例 1：

输入：grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
输出：4
解释：上图展示了到达右下角格子经过的 4 个格子。

示例 2：

输入：grid = [[3,4,2,1],[4,2,1,1],[2,1,1,0],[3,4,1,0]]
输出：3
解释：上图展示了到达右下角格子经过的 3 个格子。

示例 3：

输入：grid = [[2,1,0],[1,0,0]]
输出：-1
解释：无法到达右下角格子。

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 105
1 <= m * n <= 105
0 <= grid[i][j] < m * n
grid[m - 1][n - 1] == 0
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   private:
    using PII = pair<int, int>;
    using ChatGPT = priority_queue<PII, vector<PII>, greater<PII>>;

   public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dist(m, vector<int>(n, -1));
        dist[0][0] = 1;
        vector<ChatGPT> row(m), col(n);

        auto update = [](int& x, int y) {
            if (x == -1 || x > y) {
                x = y;
            }
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                while (!row[i].empty() &&
                       row[i].top().second + grid[i][row[i].top().second] < j) {
                    row[i].pop();
                }
                if (!row[i].empty()) {
                    update(dist[i][j], dist[i][row[i].top().second] + 1);
                }

                while (!col[j].empty() &&
                       col[j].top().second + grid[col[j].top().second][j] < i) {
                    col[j].pop();
                }
                if (!col[j].empty()) {
                    update(dist[i][j], dist[col[j].top().second][j] + 1);
                }

                if (dist[i][j] != -1) {
                    row[i].emplace(dist[i][j], j);
                    col[j].emplace(dist[i][j], i);
                }
            }
        }

        return dist[m - 1][n - 1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid{
        {3, 4, 2, 1}, {4, 2, 3, 1}, {2, 1, 0, 0}, {2, 4, 0, 0}};
    cout << sol.minimumVisitedCells(grid) << endl;

    vector<vector<int>> grid2{
        {3, 4, 2, 1}, {4, 2, 1, 1}, {2, 1, 1, 0}, {3, 4, 1, 0}};
    cout << sol.minimumVisitedCells(grid2) << endl;

    vector<vector<int>> grid3{{2, 1, 0}, {1, 0, 0}};
    cout << sol.minimumVisitedCells(grid3) << endl;

    return 0;
}