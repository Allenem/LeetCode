/*
3102. 最小化曼哈顿距离

给你一个下标从 0 开始的数组 points ，它表示二维平面上一些点的整数坐标，其中 points[i] = [xi, yi] 。

两点之间的距离定义为它们的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。

请你恰好移除一个点，返回移除后任意两点之间的 最大 距离可能的 最小 值。

示例 1：

输入：points = [[3,10],[5,15],[10,2],[4,4]]
输出：12
解释：移除每个点后的最大距离如下所示：
- 移除第 0 个点后，最大距离在点 (5, 15) 和 (10, 2) 之间，为 |5 - 10| + |15 - 2| = 18 。
- 移除第 1 个点后，最大距离在点 (3, 10) 和 (10, 2) 之间，为 |3 - 10| + |10 - 2| = 15 。
- 移除第 2 个点后，最大距离在点 (5, 15) 和 (4, 4) 之间，为 |5 - 4| + |15 - 4| = 12 。
- 移除第 3 个点后，最大距离在点 (5, 15) 和 (10, 2) 之间的，为 |5 - 10| + |15 - 2| = 18 。
在恰好移除一个点后，任意两点之间的最大距离可能的最小值是 12 。

示例 2：

输入：points = [[1,1],[1,1],[1,1]]
输出：0
解释：移除任一点后，任意两点之间的最大距离都是 0 。


提示：

3 <= points.length <= 105
points[i].length == 2
1 <= points[i][0], points[i][1] <= 108
*/
#include <iostream>
#include <vector>
#include <set>
#include <climits>

using namespace std;

// 方法一 ==========================================================================================================================
class Solution1 {
public:
    int minimumDistance(vector<vector<int>>& points) {
        // 方法1 曼哈顿距离 |x1-x2|+|y1-y2| 转 切比雪夫距离 max(|x1'-x2'|, |y1'-y2'|) 即x轴投影y投影的最大值
        // (x', y') 由 (x, y) 顺时针旋转 45° 再 * √2 得到
        // x' = x + y, y' = y - x 
        multiset<int> xs, ys; // 有序集合
        for (auto& p : points) {
            xs.insert(p[0] + p[1]);
            ys.insert(p[1] - p[0]);
        }

        int ans = INT_MAX;
        for (auto& p : points) {
            int x = p[0] + p[1], y = p[1] - p[0];
            xs.erase(xs.find(x));
            ys.erase(ys.find(y));

            int dx = *xs.rbegin() - *xs.begin(); // x轴投影
            int dy = *ys.rbegin() - *ys.begin(); // y轴投影
            ans = min(ans, max(dx, dy));

            xs.insert(x);
            ys.insert(y);
        }
        return ans;
    }
};


// 方法二 ==========================================================================================================================
class Solution2 {
    // 方法二：维护 最大次大、最小次小，数值 8 个：
    // x 最大次大，最小次小：max_x1, max_x2, min_x1, min_x2
    // y 最大次大，最小次小：max_y1, max_y2, min_y1, min_y2
    // 优化：只需要 4 个位置索引 max_xi, min_xi, max_yi, min_yi

    // 更新最大次大，注意是引用
    void update_max(int i, int v, int& max_i, int& max1, int& max2) {
        if (v > max1) {
            max_i = i;
            max2 = max1;
            max1 = v;
        }
        else if (v > max2) {
            max2 = v;
        }
    }

    // 更新最小次小，注意是引用
    void update_min(int i, int v, int& min_i, int& min1, int& min2) {
        if (v < min1) {
            min_i = i;
            min2 = min1;
            min1 = v;
        }
        else if (v < min2) {
            min2 = v;
        }
    }

public:
    int minimumDistance(vector<vector<int>>& points) {
        int max_xi, min_xi, max_yi, min_yi;
        int max_x1 = INT_MIN, max_x2 = INT_MIN, max_y1 = INT_MIN, max_y2 = INT_MIN;
        int min_x1 = INT_MAX, min_x2 = INT_MAX, min_y1 = INT_MAX, min_y2 = INT_MAX;

        for (int i = 0; i < points.size(); i++) {
            auto& p = points[i];
            int x = p[0] + p[1];
            int y = p[1] - p[0];
            update_max(i, x, max_xi, max_x1, max_x2);
            update_min(i, x, min_xi, min_x1, min_x2);
            update_max(i, y, max_yi, max_y1, max_y2);
            update_min(i, y, min_yi, min_y1, min_y2);
        }

        int ans = INT_MAX;
        for (int i : {max_xi, min_xi, max_yi, min_yi}) {
            // x轴投影：
            // 如果移除的当前节点 i 是max_xi，则剩余的最大x，取次大值max_x2；否则取最大值max_x1
            // 如果移除的当前节点 i 是min_xi，则剩余的最小x，取次小值min_x2；否则取最小值min_x1
            int dx = (i == max_xi ? max_x2 : max_x1) - (i == min_xi ? min_x2 : min_x1);
            // y轴投影：
            // 如果移除的当前节点 i 是max_yi，则剩余的最大y，取次大值max_y2；否则取最大值max_y1
            // 如果移除的当前节点 i 是min_yi，则剩余的最小y，取次小值min_y2；否则取最小值min_y1
            int dy = (i == max_yi ? max_y2 : max_y1) - (i == min_yi ? min_y2 : min_y1);
            ans = min(ans, max(dx, dy));
        }
        return ans;
    }
};

// 测试 ==========================================================================================================================
int main() {
    Solution1 s1;
    Solution2 s2;
    for (auto points : vector<vector<vector<int>>>{
        {{3,10},{5,15},{10,2},{4,4}},
        {{1,1},{1,1},{1,1}},
        {{0,0},{1,1},{1,0},{-1,1}},
        {{2,3},{4,5},{6,7},{8,9},{10,11},{12,13},{14,15},{16,17}}
        }) {
        cout << s1.minimumDistance(points) << endl;
        cout << s2.minimumDistance(points) << endl;
    }
    return 0;
}