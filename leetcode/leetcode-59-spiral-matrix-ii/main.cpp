#include <iostream>
#include <stdexcept>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<int>> generateMatrix(int n)
    {
        std::vector<std::vector<int>> results(n, std::vector<int>(n));

        int top = 0;
        int left = 0;
        int right = n - 1;
        int bottom = n - 1;
        int counter = 1;
        int direction = 2;

        while (top <= bottom && left <= right)
        {
            if (direction == 2) // right
            {
                for (auto i = left; i <= right; ++i)
                {
                    results[top][i] = counter++;
                }
                direction = (direction + 1) % 4;
                ++top;
            }
            else if (direction == 3) // down
            {
                for (auto i = top; i <= bottom; ++i)
                {
                    results[i][right] = counter++;
                }
                direction = (direction + 1) % 4;
                --right;
            }
            else if (direction == 0) // left
            {
                for (auto i = right; i >= left; --i)
                {
                    results[bottom][i] = counter++;
                }
                direction = (direction + 1) % 4;
                --bottom;
            }
            else if (direction == 1) // up
            {
                for (auto i = bottom; i >= top; --i)
                {
                    results[i][left] = counter++;
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
