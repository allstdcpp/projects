#include <iostream>
#include <stdexcept>
#include <vector>

class Solution
{
public:

    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix)
    {
        std::vector<int> results;
        results.reserve(matrix.size() * matrix[0].size());

        int top = 0;
        int left = 0;
        int right = matrix[0].size() - 1;
        int bottom = matrix.size() - 1;

        int direction = 2;

        while (top <= bottom && left <= right)
        {
            if (direction == 2) // right
            {
                for (auto i = left; i <= right; ++i)
                {
                    results.push_back(matrix[top][i]);
                }
                direction = (direction + 1) % 4;
                ++top;
            }
            else if (direction == 3) // down
            {
                for (auto i = top; i <= bottom; ++i)
                {
                    results.push_back(matrix[i][right]);
                }
                direction = (direction + 1) % 4;
                --right;
            }
            else if (direction == 0) // left
            {
                for (auto i = right; i >= left; --i)
                {
                    results.push_back(matrix[bottom][i]);
                }
                direction = (direction + 1) % 4;
                --bottom;
            }
            else if (direction == 1) // up
            {
                for (auto i = bottom; i >= top; --i)
                {
                    results.push_back(matrix[i][left]);
                }
                direction = (direction + 1) % 4;
                ++left;
            }
            else
            {
                throw std::logic_error("Invalid case.");
            }
        }

        return results;
    }
};

int main(int argc, char** argv) {}
