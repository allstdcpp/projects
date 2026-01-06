#include <functional>
#include <iostream>
#include <vector>

class Solution
{
public:
    int findMin(std::vector<int>& n)
    {
        int lo = 0;
        int hi = n.size() - 1;

        auto minimum = n[0];

        while (lo <= hi)
        {
            auto mid = lo + (hi - lo) / 2;
            if (n[lo] <= n[mid]) // sorted half
            {
                minimum = std::min(n[lo], minimum);
                lo = mid + 1;
            }
            else
            {
                if (n[mid] <= n[hi])
                {
                    minimum = std::min(n[mid], minimum);
                    hi = mid - 1;
                }
                else
                {
                    lo = mid + 1;
                }
            }
        }

        return minimum;
    }
};

int main(int argc, char** argv)
{
    std::vector<int> vs{3, 4, 5, 6, 7, 8, 0, 1, 2};
    Solution s;
    int result = s.search(vs, 2);

    std::cout << "Index: " << result << std::endl;
}
