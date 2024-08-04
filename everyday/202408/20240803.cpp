/*
3143. 正方形中的最多点数

给你一个二维数组 points 和一个字符串 s ，其中 points[i] 表示第 i 个点的坐标，s[i] 表示第 i 个点的 标签 。

如果一个正方形的中心在 (0, 0) ，所有边都平行于坐标轴，且正方形内 不 存在标签相同的两个点，那么我们称这个正方形是 合法 的。

请你返回 合法 正方形中可以包含的 最多 点数。

注意：

如果一个点位于正方形的边上或者在边以内，则认为该点位于正方形内。

正方形的边长可以为零。


示例 1：

输入：points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"

输出：2

解释：

边长为 4 的正方形包含两个点 points[0] 和 points[1] 。


示例 2：

输入：points = [[1,1],[-2,-2],[-2,2]], s = "abb"

输出：1

解释：

边长为 2 的正方形包含 1 个点 points[0] 。


示例 3：

输入：points = [[1,1],[-1,-1],[2,-2]], s = "ccd"

输出：0

解释：

任何正方形都无法只包含 points[0] 和 points[1] 中的一个点，所以合法正方形中都不包含任何点。


提示：

1 <= s.length, points.length <= 105
points[i].length == 2
-109 <= points[i][0], points[i][1] <= 109
s.length == points.length
points 中的点坐标互不相同。
s 只包含小写英文字母。
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {
        // vector dis('z' + 1, INT_MAX);
        vector<int> dis('z' + 1, INT_MAX);
        int edge = INT_MAX - 1;
        for (int i = 0; i < s.size(); i++) {
            int d = max(abs(points[i][0]), abs(points[i][1]));
            if (dis[s[i]] != INT_MAX) {
                // 取边界要标签冲突时的最大值(取不到，所以最后是＜)
                edge = min(edge, max(d, dis[s[i]]));
            }
            // 下次循环，要最小值
            dis[s[i]] = min(dis[s[i]], d);
        }
        // return ranges::count_if(dis, [&](int i) { return i < edge; });
        int res = 0;
        for (int i = 0; i < dis.size(); i++) {
            if (dis[i] < edge) {
                res++;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> points = {{2, 2}, {-1, -2}, {-4, 4}, {-3, 1}, {3, -3}};
    string str = "abdca";
    cout << s.maxPointsInsideSquare(points, str) << endl;

    vector<vector<int>> points2 = {{1, 1}, {-2, -2}, {-2, 2}};
    string str2 = "abb";
    cout << s.maxPointsInsideSquare(points2, str2) << endl;

    vector<vector<int>> points3 = {{1, 1}, {-1, -1}, {2, -2}};
    string str3 = "ccd";
    cout << s.maxPointsInsideSquare(points3, str3) << endl;

    return 0;
}