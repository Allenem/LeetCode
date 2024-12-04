/*
2056. 棋盘上有效移动组合的数目

有一个 8 x 8 的棋盘，它包含 n 个棋子（棋子包括车，后和象三种）。给你一个长度为 n 的字符串数组 pieces ，其中 pieces[i] 表示第 i 个棋子的类型（车，后或象）。除此以外，还给你一个长度为 n 的二维整数数组 positions ，其中 positions[i] = [ri, ci] 表示第 i 个棋子现在在棋盘上的位置为 (ri, ci) ，棋盘下标从 1 开始。

棋盘上每个棋子都可以移动 至多一次 。每个棋子的移动中，首先选择移动的 方向 ，然后选择 移动的步数 ，同时你要确保移动过程中棋子不能移到棋盘以外的地方。棋子需按照以下规则移动：

车可以 水平或者竖直 从 (r, c) 沿着方向 (r+1, c)，(r-1, c)，(r, c+1) 或者 (r, c-1) 移动。
后可以 水平竖直或者斜对角 从 (r, c) 沿着方向 (r+1, c)，(r-1, c)，(r, c+1)，(r, c-1)，(r+1, c+1)，(r+1, c-1)，(r-1, c+1)，(r-1, c-1) 移动。
象可以 斜对角 从 (r, c) 沿着方向 (r+1, c+1)，(r+1, c-1)，(r-1, c+1)，(r-1, c-1) 移动。

移动组合 包含所有棋子的 移动 。每一秒，每个棋子都沿着它们选择的方向往前移动 一步 ，直到它们到达目标位置。所有棋子从时刻 0 开始移动。如果在某个时刻，两个或者更多棋子占据了同一个格子，那么这个移动组合 不有效 。

请你返回 有效 移动组合的数目。

注意：

初始时，不会有两个棋子 在 同一个位置 。
有可能在一个移动组合中，有棋子不移动。
如果两个棋子 直接相邻 且两个棋子下一秒要互相占据对方的位置，可以将它们在同一秒内 交换位置 。



示例 1:

输入：pieces = ["rook"], positions = [[1,1]]
输出：15
解释：上图展示了棋子所有可能的移动。



示例 2：

输入：pieces = ["queen"], positions = [[1,1]]
输出：22
解释：上图展示了棋子所有可能的移动。


示例 3:

输入：pieces = ["bishop"], positions = [[4,3]]
输出：12
解释：上图展示了棋子所有可能的移动。


示例 4:

输入：pieces = ["rook","rook"], positions = [[1,1],[8,8]]
输出：223
解释：每个车有 15 种移动，所以总共有 15 * 15 = 225 种移动组合。
但是，有两个是不有效的移动组合：
- 将两个车都移动到 (8, 1) ，会导致它们在同一个格子相遇。
- 将两个车都移动到 (1, 8) ，会导致它们在同一个格子相遇。
所以，总共有 225 - 2 = 223 种有效移动组合。
注意，有两种有效的移动组合，分别是一个车在 (1, 8) ，另一个车在 (8, 1) 。
即使棋盘状态是相同的，这两个移动组合被视为不同的，因为每个棋子移动操作是不相同的。


示例 5：

输入：pieces = ["queen","bishop"], positions = [[5,7],[3,4]]
输出：281
解释：总共有 12 * 24 = 288 种移动组合。
但是，有一些不有效的移动组合：
- 如果后停在 (6, 7) ，它会阻挡象到达 (6, 7) 或者 (7, 8) 。
- 如果后停在 (5, 6) ，它会阻挡象到达 (5, 6) ，(6, 7) 或者 (7, 8) 。
- 如果象停在 (5, 2) ，它会阻挡后到达 (5, 2) 或者 (5, 1) 。
在 288 个移动组合当中，281 个是有效的。
 

提示：

n == pieces.length 
n == positions.length
1 <= n <= 4
pieces 只包含字符串 "rook" ，"queen" 和 "bishop" 。
棋盘上最多只有一个后。
1 <= ri, ci <= 8
每一个 positions[i] 互不相同。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Move {
    int x0, y0; // 起点
    int dx, dy; // 移动方向
    int step;   // 移动次数
    
    // 默认构造函数
    Move() : x0(0), y0(0), dx(0), dy(0), step(0) {}

    // 带五个 int 参数的构造函数
    Move(int x0_, int y0_, int dx_, int dy_, int step_)
        : x0(x0_), y0(y0_), dx(dx_), dy(dy_), step(step_) {}
};

class Solution {
    vector<pair<int, int>> DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}}; // 上下左右 + 斜向
    unordered_map<char, vector<pair<int, int>>> PIECE_DIRS = {
        {'r', {DIRS.begin(), DIRS.begin() + 4}},
        {'b', {DIRS.begin() + 4, DIRS.end()}},
        {'q', DIRS},
    };

    // 计算位于 (x0,y0) 的棋子在 dirs 这些方向上的所有合法移动
    vector<Move> generate_moves(int x0, int y0, vector<pair<int, int>>& dirs) {
        const int SIZE = 8;
        vector<Move> moves = {{x0, y0, 0, 0, 0}}; // 原地不动
        for (auto [dx, dy] : dirs) {
            // 往 d 方向走 1,2,3,... 步
            int x = x0 + dx, y = y0 + dy;
            for (int step = 1; 0 < x && x <= SIZE && 0 < y && y <= SIZE; step++) {
                moves.emplace_back(x0, y0, dx, dy, step);
                x += dx;
                y += dy;
            }
        }
        return moves;
    }

    // 判断两个移动是否合法，即不存在同一时刻两个棋子重叠的情况
    bool is_valid(Move& m1, Move& m2) {
        int x1 = m1.x0, y1 = m1.y0;
        int x2 = m2.x0, y2 = m2.y0;
        for (int i = 0; i < max(m1.step, m2.step); i++) {
            // 每一秒走一步
            if (i < m1.step) {
                x1 += m1.dx;
                y1 += m1.dy;
            }
            if (i < m2.step) {
                x2 += m2.dx;
                y2 += m2.dy;
            }
            if (x1 == x2 && y1 == y2) { // 重叠
                return false;
            }
        }
        return true;
    }

public:
    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        int n = pieces.size();
        // 预处理所有合法移动
        vector<vector<Move>> all_moves(n);
        for (int i = 0; i < n; i++) {
            all_moves[i] = generate_moves(positions[i][0], positions[i][1], PIECE_DIRS[pieces[i][0]]);
        }

        vector<Move> path(n); // 注意 path 的长度是固定的
        int ans = 0;
        auto dfs = [&](auto& dfs, int i) -> void {
            if (i == n) {
                ans++;
                return;
            }
            // 枚举当前棋子的所有合法移动
            for (Move& move1 : all_moves[i]) {
                // 判断合法移动 move1 是否有效
                bool ok = true;
                for (int j = 0; j < i; j++) {
                    if (!is_valid(move1, path[j])) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    path[i] = move1; // 直接覆盖，无需恢复现场
                    dfs(dfs, i + 1); // 枚举后续棋子的所有合法移动组合
                }
            }
        };
        dfs(dfs, 0);
        return ans;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/number-of-valid-move-combinations-on-chessboard/solutions/1075478/go-mo-ni-by-endlesscheng-kjpt/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    Solution s;
    vector<string> pieces = {"rook"};
    vector<vector<int>> positions = {{1, 1}};
    cout << s.countCombinations(pieces, positions) << endl;

    pieces = {"queen"};
    positions = {{1, 1}};
    cout << s.countCombinations(pieces, positions) << endl;

    pieces = {"bishop"};
    positions = {{4, 3}};
    cout << s.countCombinations(pieces, positions) << endl;

    pieces = {"rook", "rook"};
    positions = {{1, 1}, {8, 8}};
    cout << s.countCombinations(pieces, positions) << endl;

    pieces = {"queen", "bishop"};
    positions = {{5, 7}, {3, 4}};
    cout << s.countCombinations(pieces, positions) << endl;
    return 0;
}