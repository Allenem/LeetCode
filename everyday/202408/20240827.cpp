/*
3134. 找出唯一性数组的中位数

给你一个整数数组 nums 。数组 nums 的 唯一性数组 是一个按元素从小到大排序的数组，包含了 nums 的所有 **非空子数组中** 不同元素的个数。

换句话说，这是由所有 0 <= i <= j < nums.length 的 distinct(nums[i..j]) 组成的递增数组。

其中，distinct(nums[i..j]) 表示从下标 i 到下标 j 的子数组中不同元素的数量。

返回 nums 唯一性数组 的 中位数 。

注意，数组的 中位数 定义为有序数组的中间元素。如果有两个中间元素，则取值较小的那个。



示例 1：

输入：nums = [1,2,3]

输出：1

解释：

nums 的唯一性数组为 [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])]，即 [1, 1, 1, 2, 2, 3] 。唯一性数组的中位数为 1 ，因此答案是 1 。



示例 2：

输入：nums = [3,4,3,4,5]

输出：2

解释：

nums 的唯一性数组为 [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3] 。唯一性数组的中位数为 2 ，因此答案是 2 。



示例 3：

输入：nums = [4,3,5,4]

输出：2

解释：

nums 的唯一性数组为 [1, 1, 1, 1, 2, 2, 2, 3, 3, 3] 。唯一性数组的中位数为 2 ，因此答案是 2 。

 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 105
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int medianOfUniquenessArray(vector<int>& nums) {
        int n = nums.size();
        long long median = ((long long) n * (n + 1) / 2 + 1) / 2;

        /* 检测数组中不同元素数目小于等于 t 的连续子数组数目是否大于等于 median */
        auto check = [&](int t) -> bool {
            unordered_map<int, int> cnt;
            long long tot = 0;
            for (int i = 0, j = 0; i < n; i++) {
                cnt[nums[i]]++;
                while (cnt.size() > t) {
                    cnt[nums[j]]--;
                    if (cnt[nums[j]] == 0) {
                        cnt.erase(nums[j]);
                    }
                    j++;
                }
                tot += i - j + 1;
            }
            return tot >= median;
        };

        int res = 0;
        int lo = 1, hi = n;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;            
            if (check(mid)) {
                res = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 3};
    cout << solution.medianOfUniquenessArray(nums) << endl;

    nums = {3, 4, 3, 4, 5};
    cout << solution.medianOfUniquenessArray(nums) << endl;

    nums = {4, 3, 5, 4};
    cout << solution.medianOfUniquenessArray(nums) << endl;
    
    return 0;
}