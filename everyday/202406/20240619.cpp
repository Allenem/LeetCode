/*
2713. 矩阵中严格递增的单元格数

给你一个下标从 1 开始、大小为 m x n 的整数矩阵 mat，你可以选择任一单元格作为 起始单元格 。

从起始单元格出发，你可以移动到 同一行或同一列 中的任何其他单元格，但前提是目标单元格的值 严格大于 当前单元格的值。

你可以多次重复这一过程，从一个单元格移动到另一个单元格，直到无法再进行任何移动。

请你找出从某个单元开始访问矩阵所能访问的 单元格的最大数量 。

返回一个表示可访问单元格最大数量的整数。

示例 1：

输入：mat = [[3,1],[3,4]]
输出：2
解释：上图展示了从第 1 行、第 2 列的单元格开始，可以访问 2 个单元格。可以证明，无论从哪个单元格开始，最多只能访问 2 个单元格，因此答案是 2 。

示例 2：

输入：mat = [[1,1],[1,1]]
输出：1
解释：由于目标单元格必须严格大于当前单元格，在本示例中只能访问 1 个单元格。

示例 3：

输入：mat = [[3,1,6],[-9,5,7]]
输出：4
解释：上图展示了从第 2 行、第 1 列的单元格开始，可以访问 4 个单元格。可以证明，无论从哪个单元格开始，最多只能访问 4 个单元格，因此答案是 4 。

提示：

m == mat.length
n == mat[i].length
1 <= m, n <= 105
1 <= m * n <= 105
-105 <= mat[i][j] <= 105
*/
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int maxIncreasingCells(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        map<int, vector<pair<int, int>>> g;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                g[mat[i][j]].emplace_back(i, j); // 相同元素放在同一组，统计位置
            }
        }
        vector<int> r(m), c(n);
        for (auto& [_, pos] : g) {
            vector<int> mx; // 先把最大值算出来，再更新 row_max 和 col_max
            for (auto& [i, j] : pos) {
                mx.push_back(max(r[i], c[j]) + 1);
            }
            for (int k = 0;k < pos.size();k++) {
                auto& [i, j] = pos[k];
                r[i] = max(r[i], mx[k]); // 更新第 i 行的最大 f 值
                c[j] = max(c[j], mx[k]); // 更新第 j 列的最大 f 值
            }
        }
        return ranges::max(r);
    }
};

int main() {
    Solution sol;
    for (auto mat : {
        vector<vector<int>>{{3, 1}, {3, 4}},
        vector<vector<int>>{{1, 1}, {1, 1}},
        vector<vector<int>>{{3, 1, 6}, {-9, 5, 7}}
        }) {
        cout << sol.maxIncreasingCells(mat) << endl;
    }
    return 0;
}

// g++ 20240619.cpp -std=c++20