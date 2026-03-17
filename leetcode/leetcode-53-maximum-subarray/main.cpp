#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

class Solution
{
public:
    int maxSubArray(std::vector<int>& nums)
    {
        int max = nums[0];
        int current = nums[0];
        int i = 1;

        while (i < nums.size())
        {
            current = std::max(nums[i], current + nums[i]);
            max = std::max(max, current);
            ++i;
        }
        return max;
    }
};

int main(int argc, char** argv) {}
