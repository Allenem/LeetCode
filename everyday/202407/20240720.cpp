/*
2850. 将石头分散到网格图的最少移动次数

给你一个大小为 3 * 3 ，下标从 0 开始的二维整数矩阵 grid ，分别表示每一个格子里石头的数目。网格图中总共恰好有 9 个石头，一个格子里可能会有 多个 石头。

每一次操作中，你可以将一个石头从它当前所在格子移动到一个至少有一条公共边的相邻格子。

请你返回每个格子恰好有一个石头的 最少移动次数 。

示例 1：

1 1 0
1 1 1
1 2 1

输入：grid = [[1,1,0],[1,1,1],[1,2,1]]
输出：3
解释：让每个格子都有一个石头的一个操作序列为：
1 - 将一个石头从格子 (2,1) 移动到 (2,2) 。
2 - 将一个石头从格子 (2,2) 移动到 (1,2) 。
3 - 将一个石头从格子 (1,2) 移动到 (0,2) 。
总共需要 3 次操作让每个格子都有一个石头。
让每个格子都有一个石头的最少操作次数为 3 。

示例 2：

1 3 0
1 0 0
1 0 3

输入：grid = [[1,3,0],[1,0,0],[1,0,3]]
输出：4
解释：让每个格子都有一个石头的一个操作序列为：
1 - 将一个石头从格子 (0,1) 移动到 (0,2) 。
2 - 将一个石头从格子 (0,1) 移动到 (1,1) 。
3 - 将一个石头从格子 (2,2) 移动到 (1,2) 。
4 - 将一个石头从格子 (2,2) 移动到 (2,1) 。
总共需要 4 次操作让每个格子都有一个石头。
让每个格子都有一个石头的最少操作次数为 4 。

提示：

grid.length == grid[i].length == 3
0 <= grid[i][j] <= 9
grid 中元素之和为 9 。


____________________________________________________________________________________________________________________

解法一：回溯。
rc为目标点，ij为当前有石子的点，
取出石子
计算当前点对[rc][ij]的曼哈顿距离|r-i|+|c-j|并加上下一步的结果backtrack(r,c+1)，每次都比较其与ans大小
放回石子

解法二：全排列。
先获取数量>1点集合from, =0的集合to
然后使用c++的next_permutation全排列遍历
每一种排列，取from[i] to[i]曼哈顿距离和step +=|from[i].first - to[i].first|+|from[i].second - to[i].second|最小

解法三：DFS
先获取数量>1点集合from, =0的集合to
DFS遍历from和mask（是根据from个数制定的二进制模板，一一对应，用于筛选to）
DFS内部for遍历to并且需与mask匹配
计算当前点对from[i], to[j]的曼哈顿距离|from[i].first - to[i].first|+|from[i].second - to[i].second|并加上下一步的结果dfs(i+1, mask^(1<<j))，每次都比较其与ans大小

作者：allenem
链接：https://leetcode.cn/problems/minimum-moves-to-spread-stones-over-grid/solutions/2850649/hui-su-quan-pai-lie-dfssan-chong-fang-fa-ci04/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class Solution1 {
public:
    int minimumMoves(vector<vector<int>>& grid) {

        function<int(int, int)>backtrack = [&](int r, int c) -> int {
            if (r == 3) return 0; // 如果行号已经超出最后一行，则返回0
            if (c == 3) return backtrack(r + 1, 0); // 如果列号已经超出最后一列，则移动到下一行的第一个元素

            int ans = 18; // 初始化答案为一个较大的值，18是一个上限[[9,0,0],[0,0,0],[0,0,0]]
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (grid[i][j] > 0) { // 每次大于0的格子[i][j]都尝试一下移动到[r][c]
                        grid[i][j]--; // 取出一个石头
                        ans = min(ans, abs(r - i) + abs(c - j) + backtrack(r, c + 1)); // 计算当前格子的曼哈顿距离并加上下一步的结果
                        grid[i][j]++; // 回溯，将石头放回原位
                    }
                }
            }
            return ans;
            };

        return backtrack(0, 0);
    }
};

class Solution2 {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<pair<int, int>> from, to;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] > 1) {
                    for (int k = 2; k <= grid[i][j]; ++k) {
                        from.emplace_back(i, j);
                    }
                }
                else if (grid[i][j] == 0) to.emplace_back(i, j);
            }
        }

        int ans = 18;
        do {
            int step = 0;
            for (int i = 0; i < from.size(); i++) {
                step += abs(from[i].first - to[i].first) + abs(from[i].second - to[i].second);
            }
            ans = min(ans, step);
        } while (next_permutation(from.begin(), from.end()));
        return ans;
    }
};

class Solution3 {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        vector<pair<int, int>> from, to;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] > 1) {
                    for (int k = 2; k <= grid[i][j]; ++k) {
                        from.emplace_back(i, j);
                    }
                }
                else if (grid[i][j] == 0) to.emplace_back(i, j);
            }
        }

        if (!from.size()) return 0;
        function<int(int, int)> dfs = [&](int i, int mask)->int {
            if (i == from.size())return 0;
            int ans = 18;
            for (int j = 0; j < to.size();j++) {
                if (mask & (1 << j)) {
                    ans = min(ans, abs(from[i].first - to[j].first) + abs(from[i].second - to[j].second) + dfs(i + 1, mask ^ (1 << j)));
                }
            }
            return ans;
            };

        return dfs(0, (1 << from.size()) - 1);
    }
};

int main() {
    Solution1 s1;
    Solution2 s2;
    Solution3 s3;
    vector<vector<vector<int>>> grids = {
        {{1,1,0},{1,1,1},{1,2,1}},
        {{1,3,0},{1,0,0},{1,0,3}}
    };

    for (auto& grid : grids) {
        cout << s1.minimumMoves(grid) << endl;
        cout << s2.minimumMoves(grid) << endl;
        cout << s3.minimumMoves(grid) << endl;
    }
    return 0;
}