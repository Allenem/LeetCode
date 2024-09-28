/*
2286. 以组为单位订音乐会的门票

一个音乐会总共有 n 排座位，编号从 0 到 n - 1 ，每一排有 m 个座椅，编号为 0 到 m - 1 。你需要设计一个买票系统，针对以下情况进行座位安排：

- 同一组的 k 位观众坐在 同一排座位，且座位连续 。
- k 位观众中 每一位 都有座位坐，但他们 不一定 坐在一起。

由于观众非常挑剔，所以：

- 只有当一个组里所有成员座位的排数都 小于等于 maxRow ，这个组才能订座位。每一组的 maxRow 可能 不同 。
- 如果有多排座位可以选择，优先选择 最小 的排数。如果同一排中有多个座位可以坐，优先选择号码 最小 的。

请你实现 BookMyShow 类：

 BookMyShow(int n, int m) ，初始化对象，n 是排数，m 是每一排的座位数。
 int[] gather(int k, int maxRow) 返回长度为 2 的数组，表示 k 个成员中 第一个座位 的排数和座位编号，这 k 位成员必须坐在 同一排座位，且座位连续 。换言之，返回最小可能的 r 和 c 满足第 r 排中 [c, c + k - 1] 的座位都是空的，且 r <= maxRow 。如果 无法 安排座位，返回 [] 。
 boolean scatter(int k, int maxRow) 如果组里所有 k 个成员 不一定 要坐在一起的前提下，都能在第 0 排到第 maxRow 排之间找到座位，那么请返回 true 。这种情况下，每个成员都优先找排数 最小 ，然后是座位编号最小的座位。如果不能安排所有 k 个成员的座位，请返回 false 。


示例 1：

输入：
["BookMyShow", "gather", "gather", "scatter", "scatter"]
[[2, 5], [4, 0], [2, 0], [5, 1], [5, 1]]
输出：
[null, [0, 0], [], true, false]

解释：
BookMyShow bms = new BookMyShow(2, 5); // 总共有 2 排，每排 5 个座位。
bms.gather(4, 0); // 返回 [0, 0]
                  // 这一组安排第 0 排 [0, 3] 的座位。
bms.gather(2, 0); // 返回 []
                  // 第 0 排只剩下 1 个座位。
                  // 所以无法安排 2 个连续座位。
bms.scatter(5, 1); // 返回 True
                   // 这一组安排第 0 排第 4 个座位和第 1 排 [0, 3] 的座位。
bms.scatter(5, 1); // 返回 False
                   // 总共只剩下 1 个座位。
 

提示：

1 <= n <= 5 * 104
1 <= m, k <= 109
0 <= maxRow <= n - 1
gather 和 scatter 总 调用次数不超过 5 * 104 次。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class BookMyShow {
    int n, m;
    vector<int> mn;
    vector<int long> sum;

    // 把下标 i 上的元素值增加 val
    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            mn[o] += val;
            sum[o] += val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, i, val);
        } else {
            update(o * 2 + 1, m + 1, r, i, val);
        }
        mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }

    // 返回区间 [L,R] 内的元素和
    long long querySum(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return sum[o];
        }
        long long res = 0;
        int m = (l + r) / 2;
        if (L <= m) {
            res = querySum(o * 2, l, m, L, R);
        }
        if (R > m) {
            res += querySum(o * 2 + 1, m + 1, r, L, R);
        }
        return res;
    }

    // 返回区间 [0,R] 中 <= val 的最靠左的位置，不存在时返回 -1
    int findFirst(int o, int l, int r, int R, int val) {
        if (mn[o] > val) {
            return -1; // 整个区间的元素值都大于 val
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        if (mn[o * 2] <= val) {
            return findFirst(o * 2, l, m, R, val);
        }
        if (R > m) {
            return findFirst(o * 2 + 1, m + 1, r, R, val);
        }
        return -1;
    }

public:
    BookMyShow(int n, int m) : n(n), m(m), mn(4 << __lg(n)), sum(4 << __lg(n)) {}

    vector<int> gather(int k, int maxRow) {
        // 找第一个能倒入 k 升水的水桶
        int r = findFirst(1, 0, n - 1, maxRow, m - k);
        if (r < 0) { // 没有这样的水桶
            return {};
        }
        int c = querySum(1, 0, n - 1, r, r);
        update(1, 0, n - 1, r, k); // 倒水
        return {r, c};
    }

    bool scatter(int k, int maxRow) {
        // [0,maxRow] 的接水量之和
        long long s = querySum(1, 0, n - 1, 0, maxRow);
        if (s > (long long) m * (maxRow + 1) - k) {
            return false; // 水桶已经装了太多的水
        }
        // 从第一个没有装满的水桶开始
        int i = findFirst(1, 0, n - 1, maxRow, m - 1);
        while (k) {
            int left = min(m - (int) querySum(1, 0, n - 1, i, i), k);
            update(1, 0, n - 1, i, left); // 倒水
            k -= left;
            i++;
        }
        return true;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/booking-concert-tickets-in-groups/solutions/1523876/by-endlesscheng-okcu/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    BookMyShow bms(2, 5);

    vector<int> res;
    res = bms.gather(4, 0);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;

    res = bms.gather(2, 0);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;

    cout << boolalpha;
    cout << bms.scatter(5, 1) << endl;
    cout << bms.scatter(5, 1) << endl;
    return 0;
}