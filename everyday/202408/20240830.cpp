/*
3153. 所有数对中数位差之和

你有一个数组 nums ，它只包含 正 整数，所有正整数的数位长度都 相同 。

两个整数的 数位差 指的是两个整数 相同 位置上不同数字的数目。

请你返回 nums 中 所有 整数对里，数位差之和。
 

示例 1：

输入：nums = [13,23,12]

输出：4

解释：
计算过程如下：
- 13 和 23 的数位差为 1 。
- 13 和 12 的数位差为 1 。
- 23 和 12 的数位差为 2 。
所以所有整数数对的数位差之和为 1 + 1 + 2 = 4 。


示例 2：

输入：nums = [10,10,10,10]

输出：0

解释：
数组中所有整数都相同，所以所有整数数对的数位不同之和为 0 。


提示：

2 <= nums.length <= 105
1 <= nums[i] < 109
nums 中的整数都有相同的数位长度。
*/

#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        auto ans = 0ll;
        // 每个元素数位长度相同，所以遍历各个数位，i/10
        while (nums[0]) {
            // 对于每个数位，10位数都重置为0
            vector cnt(10, 0ll); 
            for (int& i : nums) {
                cnt[i % 10]++;
                i /= 10;
            }
            // 某一数位i不同次数 (n - cnt[i]) * cnt[i] / 2
            // 总和 (∑_(i=0)^9 (n - cnt[i]) * cnt[i]) / 2
            ans += accumulate(cnt.begin(), cnt.end(), 0ll, [&](auto a, auto b) { return a + (nums.size() - b) * b; });
        }
        return ans / 2;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {13, 23, 12};
    cout << solution.sumDigitDifferences(nums) << endl;

    nums = {10, 10, 10, 10};
    cout << solution.sumDigitDifferences(nums) << endl;

    return 0;
}