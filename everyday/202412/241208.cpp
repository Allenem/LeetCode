/*
782. 变为棋盘

一个 n x n 的二维网络 board 仅由 0 和 1 组成 。每次移动，你能交换任意两列或是两行的位置。

返回 将这个矩阵变为  “棋盘”  所需的最小移动次数 。如果不存在可行的变换，输出 -1。

“棋盘” 是指任意一格的上下左右四个方向的值均与本身不同的矩阵。

示例 1:

输入: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
输出: 2
解释:一种可行的变换方式如下，从左到右：
第一次移动交换了第一列和第二列。
第二次移动交换了第二行和第三行。

示例 2:

输入: board = [[0, 1], [1, 0]]
输出: 0
解释: 注意左上角的格值为0时也是合法的棋盘，也是合法的棋盘.


示例 3:

输入: board = [[1, 0], [1, 0]]
输出: -1
解释: 任意的变换都不能使这个输入变为合法的棋盘。
 

提示：

n == board.length
n == board[i].length
2 <= n <= 30
board[i][j] 将只包含 0或 1
*/
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        auto& first_row = board[0];
        vector<int> first_col(n);
        int row_cnt[2]{}, col_cnt[2]{};
        for (int i = 0; i < n; i++) {
            row_cnt[first_row[i]]++; // 统计 0 和 1 的个数
            first_col[i] = board[i][0];
            col_cnt[first_col[i]]++;
        }

        // 第一行，0 和 1 的个数之差不能超过 1
        // 第一列，0 和 1 的个数之差不能超过 1
        if (abs(row_cnt[0] - row_cnt[1]) > 1 || abs(col_cnt[0] - col_cnt[1]) > 1) {
            return -1;
        }

        // 每一行和第一行比较，要么完全相同，要么完全不同
        for (auto& row : board) {
            bool same = row[0] == first_row[0];
            for (int i = 0; i < n; i++) {
                if ((row[i] == first_row[i]) != same) {
                    return -1;
                }
            }
        }

        // 计算最小交换次数
        auto min_swap = [&](vector<int>& arr, int cnt[2]) {
            int x0 = cnt[1] > cnt[0]; // 如果 n 是偶数，x0 是 0
            int diff = 0;
            for (int i = 0; i < n; i++) {
                diff += i % 2 ^ arr[i] ^ x0;
            }
            return n % 2 ? diff / 2 : min(diff, n - diff) / 2;
        };

        return min_swap(first_row, row_cnt) + min_swap(first_col, col_cnt);
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/transform-to-chessboard/solutions/2997293/tu-jie-ni-xiang-si-wei-pythonjavaccgojsr-mixb/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution s;
    vector<vector<int>> board = {{0,1,1,0},{0,1,1,0},{1,0,0,1},{1,0,0,1}};
    cout << s.movesToChessboard(board) << endl;

    board = {{0, 1}, {1, 0}};
    cout << s.movesToChessboard(board) << endl;

    board = {{1, 0}, {1, 0}};
    cout << s.movesToChessboard(board) << endl;
    return 0;
}