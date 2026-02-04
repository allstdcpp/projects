#include <unordered_set>
#include <vector>

class Solution
{
public:

    long long : q : qmaximumSubarray(std::vector<int> n, int k)
    {
        long long max = 0;
        long long current = 0;
        std::unordered_set<int> s;

        // [1,2,3,]
        for (auto i = 0; i < n.size();)
        {
            auto [it, succ] = s.insert(n[i]);
            current += n[i];

            if (!succ)
            {
                continue;
            }

            if (i >= k - 1)
            {
                if (s.size() == k)
                {
                    max = std::max(current, max);
                    s.erase(n[(i - k) + 1]);
                }
                ++i;
            }
        }

        return max;
    }
};

int main(int argc, char** argv) { return Solution{}.maximumSubarray(std::vector{1, 1, 1, 7, 8, 9}, 3); }
