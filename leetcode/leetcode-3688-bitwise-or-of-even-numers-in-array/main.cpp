#include <functional>
#include <numeric>
#include <vector>

class Solution
{
public:
    int evenNumberBitwiseORs(std::vector<int>& nums)
    {
        return std::accumulate(nums.begin(), nums.end(), 0, [](auto a, auto b) {
            if (b & 1 ^ 1)
            {
                return a | b;
            }
            return a;
        });
    }
};

int main(int argc, char** argv) {}
