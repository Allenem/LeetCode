/*
3248. 矩阵中的蛇

大小为 n x n 的矩阵 grid 中有一条蛇。蛇可以朝 四个可能的方向 移动。矩阵中的每个单元格都使用位置进行标识： grid[i][j] = (i * n) + j。

蛇从单元格 0 开始，并遵循一系列命令移动。

给你一个整数 n 表示 grid 的大小，另给你一个字符串数组 commands，其中包括 "UP"、"RIGHT"、"DOWN" 和 "LEFT"。题目测评数据保证蛇在整个移动过程中将始终位于 grid 边界内。

返回执行 commands 后蛇所停留的最终单元格的位置。

 

示例 1：

输入：n = 2, commands = ["RIGHT","DOWN"]

输出：3

解释：

0√	1
2	3

0	1√
2	3

0	1
2	3√



示例 2：

输入：n = 3, commands = ["DOWN","RIGHT","UP"]

输出：1

解释：

0√	1	2
3	4	5
6	7	8

0	1	2
3√	4	5
6	7	8

0	1	2
3	4√	5
6	7	8

0	1√	2
3	4	5
6	7	8
 

提示：

2 <= n <= 10
1 <= commands.length <= 100
commands 仅由 "UP"、"RIGHT"、"DOWN" 和 "LEFT" 组成。
生成的测评数据确保蛇不会移动到矩阵的边界外。
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int finalPositionOfSnake(int n, vector<string>& commands) {
        int ans = 0;
        for(auto c:commands){
            if(c=="LEFT") ans--;
            else if(c=="RIGHT") ans++;
            else if(c=="UP") ans-=n;
            else ans+=n;
        }
        return ans;
    }
};

int main(){
    Solution s;
    int n = 2;
    vector<string> commands = {"RIGHT","DOWN"};
    cout<<s.finalPositionOfSnake(n, commands)<<endl;

    n = 3;
    commands = {"DOWN","RIGHT","UP"};
    cout<<s.finalPositionOfSnake(n, commands)<<endl;

    return 0;
}