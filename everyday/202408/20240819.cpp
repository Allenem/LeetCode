/*
552. 学生出勤记录 II

可以用字符串表示一个学生的出勤记录，其中的每个字符用来标记当天的出勤情况（缺勤、迟到、到场）。记录中只含下面三种字符：

'A'：Absent，缺勤
'L'：Late，迟到
'P'：Present，到场

如果学生能够 同时 满足下面两个条件，则可以获得出勤奖励：

按 总出勤 计，学生缺勤（'A'）严格 少于两天。
学生 不会 存在 连续 3 天或 连续 3 天以上的迟到（'L'）记录。

给你一个整数 n ，表示出勤记录的长度（次数）。请你返回记录长度为 n 时，可能获得出勤奖励的记录情况 数量 。答案可能很大，所以返回对 109 + 7 取余 的结果。


示例 1：

输入：n = 2
输出：8
解释：
有 8 种长度为 2 的记录将被视为可奖励：
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL" 
只有"AA"不会被视为可奖励，因为缺勤次数为 2 次（需要少于 2 次）。


示例 2：

输入：n = 1
输出：3


示例 3：

输入：n = 10101
输出：183236316
 

提示：

1 <= n <= 105
*/
#include <iostream>
#include <vector>
#include <string>
#include <array>
using namespace std;

class Solution1 {
public:
    int checkRecord(int n) {
        // 记忆化搜索：我们设计一个函数 dfs(i,j,k)，表示从第 i 个出勤记录开始，当前缺勤次数为 j，目前最后连续迟到次数为 k 时，可获得出勤奖励的情况数量
        const int MOD = 1e9 + 7;
        vector<vector<vector<int>>> f(n, vector<vector<int>>(2, vector<int>(3, -1)));

        auto dfs = [&](auto&& dfs, int i, int j, int k) -> int {
            // 遍历结束
            if(i >= n) return 1;
            // 记忆化搜索
            if(f[i][j][k] != -1) return f[i][j][k];

            // 都可以选择到场，即 dfs(i+1, j, 0)
            int ans = dfs(dfs, i+1, j, 0);
            // j == 0 可以选择不到场
            if(j == 0) ans = (ans + dfs(dfs, i+1, j+1, 0)) % MOD;
            // k < 2 可以选择迟到
            if(k < 2) ans = (ans + dfs(dfs, i+1, j, k+1)) % MOD;

            return f[i][j][k] = ans;
        };

        return dfs(dfs, 0, 0, 0);
    }
};

class Solution2 {
    
    // 矩阵快速幂
    /*
    (j,k)=(0,0),(0,1),(0,2),(1,0),(1,1),(1,2) 分别对应的 6 个状态转移方程：

    f[i][0]=f[i−1][0]+f[i−1][1]+f[i−1][3]
    f[i][1]=f[i−1][0]+f[i−1][2]+f[i−1][3]
    f[i][2]=f[i−1][0]+f[i−1][3]
    f[i][3]=f[i−1][3]+f[i−1][4]
    f[i][4]=f[i−1][3]+f[i−1][5]
    f[i][5]=f[i−1][3]

    用矩阵乘法表示，即
        
    f[i][0]         1, 1, 0, 1, 0, 0      f[i−1][0]
    f[i][1]         1, 0, 1, 1, 0, 0      f[i−1][1]
    f[i][2]    =    1, 0, 0, 1, 0, 0   x  f[i−1][2]
    f[i][3]         0, 0, 0, 1, 1, 0      f[i−1][3]
    f[i][4]         0, 0, 0, 1, 0, 1      f[i−1][4]
    f[i][5]         0, 0, 0, 1, 0, 0      f[i−1][5]

    把上式中的三个矩阵分别记作 F[i],M,F[i−1]，即
    
    F[i]=M×F[i−1]
    */
        
    static constexpr int MOD = 1'000'000'007;
    static constexpr int SIZE = 6;

    using matrix = array<array<int, SIZE>, SIZE>;

    // 返回矩阵 a 和矩阵 b 相乘的结果
    matrix mul(matrix& a, matrix& b) {
        matrix c{};
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    c[i][j] = (c[i][j] + (long long) a[i][k] * b[k][j]) % MOD;
                }
            }
        }
        return c;
    }

    // 返回 n 个矩阵 a 相乘的结果
    matrix pow(matrix a, int n) {
        matrix res = {};
        for (int i = 0; i < SIZE; i++) {
            res[i][i] = 1; // 单位矩阵
        }
        while (n) {
            if (n & 1) {
                res = mul(res, a);
            }
            a = mul(a, a);
            n >>= 1;
        }
        return res;
    }

public:
    int checkRecord(int n) {
        matrix m = {{
            {{1, 1, 0, 1, 0, 0}},
            {{1, 0, 1, 1, 0, 0}},
            {{1, 0, 0, 1, 0, 0}},
            {{0, 0, 0, 1, 1, 0}},
            {{0, 0, 0, 1, 0, 1}},
            {{0, 0, 0, 1, 0, 0}},
        }};
        matrix res = pow(m, n);
        int ans = 0;
        for (int x : res[0]) {
            ans = (ans + x) % MOD;
        }
        return ans;
    }
};

int main() {
    Solution1 s1;
    cout << s1.checkRecord(2) << endl;
    cout << s1.checkRecord(1) << endl;
    cout << s1.checkRecord(10101) << endl;

    Solution2 s2;
    cout << s2.checkRecord(2) << endl;
    cout << s2.checkRecord(1) << endl;
    cout << s2.checkRecord(10101) << endl;
    
    return 0;
}