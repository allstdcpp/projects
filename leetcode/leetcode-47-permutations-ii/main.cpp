#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> vs;

        std::vector<int> current;
        std::vector<bool> visited(nums.size(), false);

        std::sort(nums.begin(), nums.end());

        std::function<void()> f = [&]() {
            if (current.size() == nums.size())
            {
                vs.push_back(current);
                return;
            }

            for (auto i = 0; i < nums.size(); ++i)
            {
                if (visited[i] || (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]))
                    continue;

                visited[i] = true;

                current.push_back(nums[i]);
                f();
                current.pop_back();

                visited[i] = false;
            }
        };

        f();

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
