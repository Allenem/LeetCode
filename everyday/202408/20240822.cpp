/*
3133. 数组最后一个元素的最小值

给你两个整数 n 和 x 。你需要构造一个长度为 n 的 正整数 数组 nums ，对于所有 0 <= i < n - 1 ，满足 nums[i + 1] 大于 nums[i] ，并且数组 nums 中所有元素的按位 AND 运算结果为 x 。

返回 nums[n - 1] 可能的 最小 值。


示例 1：

输入：n = 3, x = 4

输出：6

解释：

数组 nums 可以是 [4,5,6] ，最后一个元素为 6 。


示例 2：

输入：n = 2, x = 7

输出：15

解释：

数组 nums 可以是 [7,15] ，最后一个元素为 15 。


提示：

1 <= n, x <= 10^8
*/

#include <immintrin.h>
#include <iostream>
using namespace std;

class Solution {
public:
    long long minEnd(int n, int x) __attribute__((target("bmi2"))) {
        return _pdep_u64(n - 1, ~uint64_t(x)) | x;
    }
};

// 这道题思路很简单，位与为 x 说明所有数的二进制位都包含 x 为子集，能变化的部分就是二进制位为 0 的部分，
// 只需要将 n−1 填进 x 的二进制中为 0 的部分即可，这个操作暴力实现是 O(logn) 的，
// 但 bmi2 指令集中刚好有 pdep 这个指令可以完成这个操作，具体见 Intel Intrinsics 
// [https://leetcode.cn/link/?target=https%3A%2F%2Fwww.intel.com%2Fcontent%2Fwww%2Fus%2Fen%2Fdocs%2Fintrinsics-guide%2Findex.html%23text%3D_pdep]。

int main() {
    Solution s;
    cout << s.minEnd(3, 4) << endl;
    cout << s.minEnd(2, 7) << endl;
    return 0;
}