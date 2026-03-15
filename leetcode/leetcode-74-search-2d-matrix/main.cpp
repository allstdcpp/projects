#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int l = 0;
        int r = matrix.size() * matrix[0].size() - 1;

        int stride = matrix[0].size();

        while (l <= r)
        {
            auto mid = l + (r - l) / 2;

            auto row = mid / stride;
            auto col = mid % stride;

            auto v = matrix[row][col];

            if (v == target)
            {
                return true;
            }
            else if (target < v)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }

        return false;
    }
};

int main(int argc, char** argv) { return 0; }
