/*
39. 组合总和

给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出
candidates 中可以使数字和为目标数 target 的 所有 不同组合
，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取
。如果至少一个数字的被选数量不同，则两种组合是不同的。

对于给定的输入，保证和为 target 的不同组合数少于 150 个。

示例 1：

输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。

示例 2：

输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]

示例 3：

输入: candidates = [2], target = 1
输出: []

提示：

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
candidates 的所有元素 互不相同
1 <= target <= 40
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        int n = candidates.size();
        vector<vector<int>> ret;
        vector<int> init;
        function<void(int, int, vector<int>)> bk = [&](int i, int presum,
                                                       vector<int> pre) {
            for (int j = i; j < n; ++j) {
                if (presum + candidates[j] > target)
                    break;
                vector<int> tmp = pre;
                tmp.push_back(candidates[j]);
                if (presum + candidates[j] == target) {
                    ret.push_back(tmp);
                    break;
                }
                bk(j, presum + candidates[j], tmp);
            }
        };
        bk(0, 0, init);
        return ret;
    }
};

int main() {
    Solution s;
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> ret = s.combinationSum(candidates, target);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    candidates = {2, 3, 5};
    target = 8;
    ret = s.combinationSum(candidates, target);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    candidates = {2};
    target = 1;
    ret = s.combinationSum(candidates, target);
    for (auto& v : ret) {
        for (int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}