/*
1847. 最近的房间

一个酒店里有 n 个房间，这些房间用二维整数数组 rooms 表示，其中 rooms[i] = [roomIdi, sizei] 表示有一个房间号为 roomIdi 的房间且它的面积为 sizei 。每一个房间号 roomIdi 保证是 独一无二 的。

同时给你 k 个查询，用二维数组 queries 表示，其中 queries[j] = [preferredj, minSizej] 。第 j 个查询的答案是满足如下条件的房间 id ：

房间的面积 至少 为 minSizej ，且

abs(id - preferredj) 的值 最小 ，其中 abs(x) 是 x 的绝对值。

如果差的绝对值有 相等 的，选择 最小 的 id 。如果 没有满足条件的房间 ，答案为 -1 。

请你返回长度为 k 的数组 answer ，其中 answer[j] 为第 j 个查询的结果。



示例 1：

输入：rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
输出：[3,-1,3]
解释：查询的答案如下：
查询 [3,1] ：房间 3 的面积为 2 ，大于等于 1 ，且号码是最接近 3 的，为 abs(3 - 3) = 0 ，所以答案为 3 。
查询 [3,3] ：没有房间的面积至少为 3 ，所以答案为 -1 。
查询 [5,2] ：房间 3 的面积为 2 ，大于等于 2 ，且号码是最接近 5 的，为 abs(3 - 5) = 2 ，所以答案为 3 。



示例 2：

输入：rooms = [[1,4],[2,3],[3,5],[4,1],[5,2]], queries = [[2,3],[2,4],[2,5]]
输出：[2,1,3]
解释：查询的答案如下：
查询 [2,3] ：房间 2 的面积为 3 ，大于等于 3 ，且号码是最接近的，为 abs(2 - 2) = 0 ，所以答案为 2 。
查询 [2,4] ：房间 1 和 3 的面积都至少为 4 ，答案为 1 因为它房间编号更小。
查询 [2,5] ：房间 3 是唯一面积大于等于 5 的，所以答案为 3 。
 

提示：

n == rooms.length
1 <= n <= 105
k == queries.length
1 <= k <= 104
1 <= roomIdi, preferredj <= 107
1 <= sizei, minSizej <= 107
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        // 按照 size 从大到小排序
        ranges::sort(rooms, {}, [](auto& a) { return -a[1]; });

        int q = queries.size();
        // 按照 minSize 从大到小排序 query_ids
        vector<int> query_ids(q);
        iota(query_ids.begin(), query_ids.end(), 0);
        ranges::sort(query_ids, {}, [&](int i) { return -queries[i][1]; });

        vector<int> ans(q, -1);
        set<int> room_ids; // 有序集合
        int j = 0;

        for (int i : query_ids) {
            int preferred_id = queries[i][0], min_size = queries[i][1];
            while (j < rooms.size() && rooms[j][1] >= min_size) {
                // >= 大的 minSize 的房间号已经添加，无需重复添加到 room_ids
                room_ids.insert(rooms[j][0]);
                j++;
            }

            int diff = INT_MAX;
            auto it = room_ids.lower_bound(preferred_id);
            // 优先小编号
            if (it != room_ids.begin()) {
                auto p = prev(it);
                diff = preferred_id - *p; // 左边的差
                ans[i] = *p;
            }
            // 只有右边大编号的绝对值更小，才替换答案
            if (it != room_ids.end() && *it - preferred_id < diff) { // 右边的差更小
                ans[i] = *it;
            }
        }
        return ans;
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/closest-room/solutions/2996902/chi-xian-you-xu-ji-he-shuang-zhi-zhen-py-jch8/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

int main() {
    vector<vector<int>> rooms = {{2,2},{1,2},{3,2}};
    vector<vector<int>> queries = {{3,1},{3,3},{5,2}};
    Solution solution;
    auto ans = solution.closestRoom(rooms, queries);
    for (auto& a : ans) {
        cout << a << " ";
    }
    cout << endl;

    rooms = {{1,4},{2,3},{3,5},{4,1},{5,2}};
    queries = {{2,3},{2,4},{2,5}};
    ans = solution.closestRoom(rooms, queries);
    for (auto& a : ans) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}
// g++ 241216.cpp -std=c++20