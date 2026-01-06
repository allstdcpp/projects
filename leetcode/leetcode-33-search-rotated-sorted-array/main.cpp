#include <functional>
#include <iostream>
#include <vector>

class Solution
{
public:
    int search(std::vector<int>& n, int t)
    {
        int lo = 0;
        int hi = n.size() - 1;

        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (n[mid] == t)
                return mid;
            else if (n[lo] <= n[mid])
            {
                if (t >= n[lo] && t <= n[mid])
                {
                    hi = mid - 1;
                }
                else
                {
                    lo = mid + 1;
                }
            }
            else
            {
                if (t >= n[mid] && t <= n[hi])
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid - 1;
                }
            }
        }

        return -1;
    }
};

int main(int argc, char** argv)
{
    std::vector<int> vs{3, 4, 5, 6, 7, 8, 0, 1, 2};
    Solution s;
    int result = s.search(vs, 2);

    std::cout << "Index: " << result << std::endl;
}
