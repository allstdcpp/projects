#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class NumArray
{
public:
    NumArray(std::vector<int>& nums)
        : prefix_sums_{nums}
    {
        std::partial_sum(nums.begin(), nums.end(), prefix_sums_.begin());
    }

    int sumRange(int left, int right)
    {
        --left;
        auto to = prefix_sums_[right];
        auto from = left < 0 ? 0 : prefix_sums_[left];

        return to - from;
    }

    std::vector<int> prefix_sums_;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

int main(int argc, char** argv) {}
