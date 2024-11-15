/*
3239. 最少翻转次数使二进制矩阵回文 I

给你一个 m x n 的二进制矩阵 grid 。

如果矩阵中一行或者一列从前往后与从后往前读是一样的，那么我们称这一行或者这一列是 回文 的。

你可以将 grid 中任意格子的值 翻转 ，也就是将格子里的值从 0 变成 1 ，或者从 1 变成 0 。

请你返回 最少 翻转次数，使得矩阵 要么 所有行是 回文的 ，要么所有列是 回文的 。

 

示例 1：

输入：grid = [[1,0,0],[0,0,0],[0,0,1]]

输出：2

解释：

1 0 0      1  0 [1]
0 0 0  ->  0  0  0
0 0 1     [1] 0  1

将高亮的格子翻转，得到所有行都是回文的。



示例 2：

输入：grid = [[0,1],[0,1],[0,0]]

输出：1

解释：

0 1      0  1
0 1  ->  0  1
0 0      0 [1] 

将高亮的格子翻转，得到所有列都是回文的。



示例 3：

输入：grid = [[1],[0]]

输出：0

解释：

所有行已经是回文的。

 

提示：

m == grid.length
n == grid[i].length
1 <= m * n <= 2 * 105
0 <= grid[i][j] <= 1
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int minrow = 0, mincol = 0;

        // row min flip
        for(int i = 0; i < m; i++){
            int l = 0, r = n-1;
            while(l < r){
                if(grid[i][l++] != grid[i][r--]) minrow++;
            }
        }

        // column min flip
        for(int j = 0; j < n; j++){
            int u = 0, d = m-1;
            while(u < d){
                if(grid[u++][j] != grid[d--][j]) mincol++;
            }
        }

        return min(minrow, mincol);
    }
};

int main(){
    Solution s;
    vector<vector<int>> grid = {{1,0,0},{0,0,0},{0,0,1}};
    cout << s.minFlips(grid) << endl;

    grid = {{0,1},{0,1},{0,0}};
    cout << s.minFlips(grid) << endl;

    grid = {{1},{0}};
    cout << s.minFlips(grid) << endl;
    return 0;
}