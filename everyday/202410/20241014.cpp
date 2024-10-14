/*
https://www.bilibili.com/video/BV1KE41137PK/ 李永乐老师讲解

887. 鸡蛋掉落

给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。

已知存在楼层 f ，满足 0 <= f <= n ，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。

每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。

请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？


示例 1：

输入：k = 1, n = 2
输出：2
解释：
鸡蛋从 1 楼掉落。如果它碎了，肯定能得出 f = 0 。 
否则，鸡蛋从 2 楼掉落。如果它碎了，肯定能得出 f = 1 。 
如果它没碎，那么肯定能得出 f = 2 。 
因此，在最坏的情况下我们需要移动 2 次以确定 f 是多少。


示例 2：

输入：k = 2, n = 6
输出：3


示例 3：

输入：k = 3, n = 14
输出：4
 

提示：

1 <= k <= 100
1 <= n <= 104
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 会超时
class Solution1 {
public:
    int superEggDrop(int k, int n) {
        if(n == 0 || n == 1 || k == 1) return n;
        int mi = n;
        // 任选一个楼层i扔鸡蛋，碎(蛋k-1，楼层前半段i-1)与不碎(蛋k, 楼层n-i)两种情况 + 本次1
        for(int i = 1; i < n; i++){
            int t = max(superEggDrop(k-1, i-1), superEggDrop(k, n-i)) + 1; // max 保证最坏情况也能测出来
            mi = min(mi, t); // min 求出最少的扔蛋次数
        }
        return mi;
    }
};

// 换个思路
class Solution2 {
public:
    // 递归，检测当前 蛋数N 当前次数T 的情况下，可测最高楼层
    int calcF(int K, int T)
    {
        if (T == 1 || K == 1) return T + 1;
        return calcF(K - 1, T - 1) + calcF(K, T - 1);
    }

    int superEggDrop(int K, int N)
    {
        int T = 1;
        while (calcF(K, T) < N + 1) T++;
        return T;
    }
};

int main(){
    Solution1 s1;
    cout << s1.superEggDrop(1, 2) << endl;
    cout << s1.superEggDrop(2, 6) << endl;
    cout << s1.superEggDrop(3, 14) << endl;
    // cout << s1.superEggDrop(3, 41) << endl; // 会超时
    cout << "====================" << endl;

    Solution2 s2;
    cout << s2.superEggDrop(1, 2) << endl;
    cout << s2.superEggDrop(2, 6) << endl;
    cout << s2.superEggDrop(3, 14) << endl;
    cout << s2.superEggDrop(3, 41) << endl;
    return 0;
}