#include <algorithm>
#include <vector>

class Solution
{
public:
    void rotate(std::vector<int>& nums, int k)
    {
        k %= nums.size();

        std::reverse(nums.begin(), nums.end());
        std::reverse(nums.begin(), nums.begin() + k);
        std::reverse(nums.begin() + k, nums.end());
    }
};

int main(int argc, char** argv) {}
