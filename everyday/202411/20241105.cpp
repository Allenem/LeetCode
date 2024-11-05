/*
3222. 求出硬币游戏的赢家

给你两个 正 整数 x 和 y ，分别表示价值为 75 和 10 的硬币的数目。

Alice 和 Bob 正在玩一个游戏。每一轮中，Alice 先进行操作，Bob 后操作。每次操作中，玩家需要拿出价值 总和 为 115 的硬币。如果一名玩家无法执行此操作，那么这名玩家 输掉 游戏。

两名玩家都采取 最优 策略，请你返回游戏的赢家。

 

示例 1：

输入：x = 2, y = 7

输出："Alice"

解释：

游戏一次操作后结束：

Alice 拿走 1 枚价值为 75 的硬币和 4 枚价值为 10 的硬币。



示例 2：

输入：x = 4, y = 11

输出："Bob"

解释：

游戏 2 次操作后结束：

Alice 拿走 1 枚价值为 75 的硬币和 4 枚价值为 10 的硬币。
Bob 拿走 1 枚价值为 75 的硬币和 4 枚价值为 10 的硬币。
 

提示：

1 <= x, y <= 100
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string losingPlayer(int x, int y) {
        string s="Bob";
        while(x/1>0 && y/4>0){
            x-=1;
            y-=4;
            s=s=="Alice"?"Bob":"Alice";
        }
        return s;
    }
};

class Solution1 {
public:
    string losingPlayer(int x, int y) {
        int ops = min(x, y / 4);
        return ops % 2 == 1 ? "Alice" : "Bob";
    }
};

int main() {
    Solution s;
    Solution1 s1;
    int x = 2, y = 7;
    cout << s.losingPlayer(x, y) << endl;
    cout << s1.losingPlayer(x, y) << endl;

    x = 4, y = 11;
    cout << s.losingPlayer(x, y) << endl;
    cout << s1.losingPlayer(x, y) << endl;

    return 0;
}