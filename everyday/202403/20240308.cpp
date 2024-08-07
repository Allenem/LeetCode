/*
2834. 找出美丽数组的最小和

给你两个正整数：n 和 target 。

如果数组 nums 满足下述条件，则称其为 美丽数组 。

nums.length == n.
nums 由两两互不相同的正整数组成。
在范围 [0, n-1] 内，不存在 两个 不同 下标 i 和 j ，使得 nums[i] + nums[j] ==
target 。 返回符合条件的美丽数组所可能具备的 最小 和，并对结果进行取模 109 + 7。

示例 1：

输入：n = 2, target = 3
输出：4
解释：nums = [1,3] 是美丽数组。
- nums 的长度为 n = 2 。
- nums 由两两互不相同的正整数组成。
- 不存在两个不同下标 i 和 j ，使得 nums[i] + nums[j] == 3 。
可以证明 4 是符合条件的美丽数组所可能具备的最小和。

示例 2：

输入：n = 3, target = 3
输出：8
解释：
nums = [1,3,4] 是美丽数组。
- nums 的长度为 n = 3 。
- nums 由两两互不相同的正整数组成。
- 不存在两个不同下标 i 和 j ，使得 nums[i] + nums[j] == 3 。
可以证明 8 是符合条件的美丽数组所可能具备的最小和。

示例 3：

输入：n = 1, target = 1
输出：1
解释：nums = [1] 是美丽数组。


提示：

1 <= n <= 109
1 <= target <= 109
*/

// 数学公式，前一半1~m和为m(1+m)/2,后一半target~target+n-m-1和为(target*2+n-m-1)/2
#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int minimumPossibleSum(int n, int target) {
        long long m = min(target / 2, n);
        return (m * (m + 1) + (n - m - 1 + target * 2) * (n - m)) / 2 %
               1'000'000'007;
    }
};

int main() {
    Solution s;
    cout << s.minimumPossibleSum(2, 3) << endl;
    cout << s.minimumPossibleSum(3, 3) << endl;
    cout << s.minimumPossibleSum(1, 1) << endl;
    return 0;
}