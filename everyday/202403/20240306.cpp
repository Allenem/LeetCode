/*
2917. 找出数组中的 K-or 值

给你一个整数数组 nums 和一个整数 k 。让我们通过扩展标准的按位或来介绍 K-or
操作。在 K-or 操作中，如果在 nums 中，至少存在 k 个元素的第 i 位值为 1 ，那么
K-or 中的第 i 位的值是 1 。

返回 nums 的 K-or 值。

示例 1：

输入：nums = [7,12,9,8,9,15], k = 4
输出：9
解释：
用二进制表示 numbers：
Number	Bit 3	Bit 2	Bit 1	Bit 0
7	0	1	1	1
12	1	1	0	0
9	1	0	0	1
8	1	0	0	0
9	1	0	0	1
15	1	1	1	1
Result = 9	1	0	0	1
位 0 在 7, 9, 9, 15 中为 1。位 3 在 12, 9, 8, 9, 15 中为 1。 只有位 0 和 3
满足。结果是 (1001)2 = 9。

示例 2：

输入：nums = [2,12,1,11,4,5], k = 6
输出：0
解释：没有位在所有 6 个数字中都为 1，如 k = 6 所需要的。所以，答案为 0。

示例 3：

输入：nums = [10,8,5,9,11,6,8], k = 1
输出：15
解释：因为 k == 1 ，数组的 1-or 等于其中所有元素按位或运算的结果。因此，答案为
10 OR 8 OR 5 OR 9 OR 11 OR 6 OR 8 = 15 。

提示：

1 <= nums.length <= 50
0 <= nums[i] < 231
1 <= k <= nums.length
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int findKOr(vector<int>& nums, int k) {
        int kor = 0, maxbit = (1 << 30);
        for (long long bit = 1; bit <= maxbit; bit <<= 1) {
            int cnt = 0;
            for (int num : nums) {
                if (num & bit) {
                    if (++cnt == k) {
                        kor |= bit;
                        break;
                    }
                }
            }
        }
        return kor;
    }
};

int main() {
    Solution s;
    vector<int> nums = {7, 12, 9, 8, 9, 15};
    int k = 4;
    cout << s.findKOr(nums, k) << endl;

    nums = {2, 12, 1, 11, 4, 5};
    k = 6;
    cout << s.findKOr(nums, k) << endl;

    nums = {10, 8, 5, 9, 11, 6, 8};
    k = 1;
    cout << s.findKOr(nums, k) << endl;

    return 0;
}