/*
688. 骑士在棋盘上的概率

在一个 n x n 的国际象棋棋盘上，一个骑士从单元格 (row, column) 开始，并尝试进行 k 次移动。行和列是 从 0 开始 的，所以左上单元格是 (0,0) ，右下单元格是 (n - 1, n - 1) 。

象棋骑士有8种可能的走法，如下图所示。每次移动在基本方向上是两个单元格，然后在正交方向上是一个单元格。

每次骑士要移动时，它都会随机从8种可能的移动中选择一种(即使棋子会离开棋盘)，然后移动到那里。

骑士继续移动，直到它走了 k 步或离开了棋盘。

返回 骑士在棋盘停止移动后仍留在棋盘上的概率 。

 

示例 1：

输入: n = 3, k = 2, row = 0, column = 0
输出: 0.0625
解释: 有两步(到(1,2)，(2,1))可以让骑士留在棋盘上。
在每一个位置上，也有两种移动可以让骑士留在棋盘上。
骑士留在棋盘上的总概率是0.0625。


示例 2：

输入: n = 1, k = 0, row = 0, column = 0
输出: 1.00000
 

提示:

1 <= n <= 25
0 <= k <= 100
0 <= row, column <= n - 1
*/
#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

class Solution {
public:
    double knightProbability(int n, int k, int row, int column) {
        vector<vector<int>> dir = {{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
        vector<vector<vector<double>>> memo;
        memo.resize(n + 1, vector<vector<double>>(n + 1, vector<double>(k + 1, -1))); // 剪枝

        function<double(int, int, int)> dfs = [&](int ki, int x, int y) -> double {
            if(ki==0) {
                memo[x][y][ki] = 1;
                return 1;
            }
            if(memo[x][y][ki] != -1) return memo[x][y][ki];
            double tmp = 0;
            for(auto d: dir){
                if(x+d[0]>-1 && x+d[0]<n && y+d[1]>-1 && y+d[1]<n){
                    tmp += dfs(ki-1, x+d[0], y+d[1]);
                }
            }
            memo[x][y][ki] = tmp;
            return tmp;
        };

        return (double)dfs(k, row, column) / pow(8, k) * 1.0;
    }
};

int main() {
    Solution s;
    cout << s.knightProbability(3, 2, 0, 0) << endl;  // 0.0625
    cout << s.knightProbability(1, 0, 0, 0) << endl;  // 1
    cout << s.knightProbability(8, 30, 6, 4) << endl; // 0.00019
    return 0;
}
