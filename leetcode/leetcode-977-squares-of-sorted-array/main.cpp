#include <iostream>
#include <vector>

class Solution
{
public:

    std::vector<int> sortedSquares(std::vector<int>& n)
    {
        std::vector<int> result(n.size());

        int l = 0;
        int r = n.size() - 1;
        int k = n.size() - 1;

        while (l <= r)
        {
            auto lv = n[l] * n[l];
            auto rv = n[r] * n[r];

            if (lv >= rv)
            {
                result[k--] = lv;
                ++l;
            }
            else
            {
                result[k--] = rv;
                r--;
            }
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
