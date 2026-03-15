#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();

        auto r = rows - 1;
        auto c = 0;

        while (r >= 0 && c < cols)
        {
            if (matrix[r][c] == target)
            {
                return true;
            }

            if (target > matrix[r][c])
            {
                c += 1;
            }
            else
            {
                r -= 1;
            }
        }
        return false;
    }
};

int main(int argc, char** argv) { return 0; }
