/*
994.腐烂的橘子

在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。

每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

--------------------------------------------------

示例 1：

minutes = 0  minutes = 1  minutes = 2  minutes = 3  minutes = 4
[[2,1,1],   [[2,2,1],   [[2,2,2],   [[2,2,2],   [[2,2,2],
 [1,1,0],    [2,1,0],    [2,2,0],    [2,2,0],    [2,2,0],
 [0,1,1]]    [0,1,1]]    [0,1,1]]    [0,2,1]]    [0,2,2]]

输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4

--------------------------------------------------

示例 2：

minutes = 0  minutes = 1  minutes = 2  minutes = 3
[[2,1,1],   [[2,2,1],   [[2,2,2],   [[2,2,2],
 [0,1,1],    [0,1,1],    [0,2,1],    [0,2,2],
 [1,0,1]]    [1,0,1]]    [1,0,2]]    [1,0,2]]

输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4
个方向上。

--------------------------------------------------

示例 3：

输入：grid = [[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    int orangesRotting(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size(), cnt = 0, ans = 0;
        queue<vector<int>> q;

        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1)
                    cnt++;
                else if (grid[i][j] == 2)
                    q.push(vector<int>{i, j});
            }
        }

        while (q.size() > 0 && cnt > 0) {
            ans++;
            int n = q.size();
            while (n--) {
                int i = q.front()[0], j = q.front()[1];
                q.pop();
                if (i - 1 >= 0 && grid[i - 1][j] == 1) {
                    grid[i - 1][j] = 2;
                    cnt--;
                    q.push(vector<int>{i - 1, j});
                }
                if (j - 1 >= 0 && grid[i][j - 1] == 1) {
                    grid[i][j - 1] = 2;
                    cnt--;
                    q.push(vector<int>{i, j - 1});
                }
                if (i + 1 < M && grid[i + 1][j] == 1) {
                    grid[i + 1][j] = 2;
                    cnt--;
                    q.push(vector<int>{i + 1, j});
                }
                if (j + 1 < N && grid[i][j + 1] == 1) {
                    grid[i][j + 1] = 2;
                    cnt--;
                    q.push(vector<int>{i, j + 1});
                }
            }
        }

        return cnt > 0 ? -1 : ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    cout << s.orangesRotting(grid) << endl;

    grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    cout << s.orangesRotting(grid) << endl;

    grid = {{0, 2}};
    cout << s.orangesRotting(grid) << endl;
}