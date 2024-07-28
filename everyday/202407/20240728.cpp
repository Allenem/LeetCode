/*
699. 掉落的方块

在二维平面上的 x 轴上，放置着一些方块。

给你一个二维整数数组 positions ，其中 positions[i] = [lefti, sideLengthi] 表示：第 i 个方块边长为 sideLengthi ，其左侧边与 x 轴上坐标点 lefti 对齐。

每个方块都从一个比目前所有的落地方块更高的高度掉落而下。方块沿 y 轴负方向下落，直到着陆到 另一个正方形的顶边 或者是 x 轴上 。一个方块仅仅是擦过另一个方块的左侧边或右侧边不算着陆。一旦着陆，它就会固定在原地，无法移动。

在每个方块掉落后，你必须记录目前所有已经落稳的 方块堆叠的最高高度 。

返回一个整数数组 ans ，其中 ans[i] 表示在第 i 块方块掉落后堆叠的最高高度。


示例 1：

6
5    o o o
4    o o o
3    o o o
2  x x
1  x x       x
0 1 2 3 4 5 6 7 8 9 10


输入：positions = [[1,2],[2,3],[6,1]]
输出：[2,5,5]
解释：
第 1 个方块掉落后，最高的堆叠由方块 1 组成，堆叠的最高高度为 2 。
第 2 个方块掉落后，最高的堆叠由方块 1 和 2 组成，堆叠的最高高度为 5 。
第 3 个方块掉落后，最高的堆叠仍然由方块 1 和 2 组成，堆叠的最高高度为 5 。
因此，返回 [2, 5, 5] 作为答案。


示例 2：

输入：positions = [[100,100],[200,100]]
输出：[100,100]
解释：
第 1 个方块掉落后，最高的堆叠由方块 1 组成，堆叠的最高高度为 100 。
第 2 个方块掉落后，最高的堆叠可以由方块 1 组成也可以由方块 2 组成，堆叠的最高高度为 100 。
因此，返回 [100, 100] 作为答案。
注意，方块 2 擦过方块 1 的右侧边，但不会算作在方块 1 上着陆。


提示：

1 <= positions.length <= 1000
1 <= lefti <= 10^8
1 <= sideLengthi <= 10^6
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size(), curmax = 0;
        vector<vector<int>>lrh;
        vector<int>ans;
        for (auto p : positions) {
            int curh = 0;
            for (auto pre : lrh) {
                if (p[0] + p[1] <= pre[0] || pre[1] <= p[0])
                    continue;
                curh = max(curh, pre[2]);
            }
            curh += p[1];
            lrh.emplace_back(vector<int>{p[0], p[0] + p[1], curh});

            curmax = max(curmax, curh);
            ans.emplace_back(curmax);
        }
        return ans;
    }
};

class Solution2 {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        int n = positions.size();
        map<int, int> hm; // 下标从first开始的高度为second,直到下一个元素。所以需要有序的map!
        hm[0] = 0;
        vector<int>ret;
        for (const auto b : positions) {
            int size = b[1];
            int l = b[0], r = b[0] + size;
            auto lit = hm.upper_bound(l); // 返回第一个大于l的元素位置，指针
            auto rit = hm.lower_bound(r); // 返回第一个大于等于r的元素位置，指针
            int rightH = prev(rit)->second;

            int maxH = 0;
            for (auto it = prev(lit);it != rit;it++) {
                maxH = max(maxH, it->second + size);
            }

            hm.erase(lit, rit); // 删除[lit, rit)之间的元素
            hm[l] = maxH;       // 插入新的元素
            if (rit == hm.end() || rit->first != r) { // 如果rit不是最后一个元素，或者rit的first不等于r：插入新的元素
                hm[r] = rightH;
            }
            ret.emplace_back(ret.empty() ? maxH : max(ret.back(), maxH)); // 返回最大值
        }
        return ret;
    }
};

int main() {
    vector<vector<vector<int>>> positions = {
        {{1,2},{2,3},{6,1}},
        {{100,100},{200,100}}
    };

    Solution1 s1;
    for (auto p : positions) {
        vector<int> ans = s1.fallingSquares(p);
        for (auto a : ans)
            cout << a << ' ';
        cout << endl;
    }

    Solution2 s2;
    for (auto p : positions) {
        vector<int> ans = s2.fallingSquares(p);
        for (auto a : ans)
            cout << a << ' ';
        cout << endl;
    }

    return 0;
}