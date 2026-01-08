#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> vs;

        std::vector<int> current;

        std::function<void()> f = [&]() {
            if (current.size() == nums.size())
            {
                vs.push_back(current);
                return;
            }

            for (auto i = 0; i < nums.size(); ++i)
            {
                if (auto it = std::find(current.begin(), current.end(), nums[i]); it != std::end(current))
                {
                    continue;
                }

                current.push_back(nums[i]);
                f();
                current.pop_back();
            }
        };

        f();

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
