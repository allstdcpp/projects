#include <climits>
#include <vector>

class Solution
{
public:

    int minPathSum(std::vector<std::vector<int>>& grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        for (auto r = rows - 1; r >= 0; --r)
        {
            for (auto c = cols - 1; c >= 0; --c)
            {
                auto bottom = INT_MAX;
                if (!(r + 1 >= rows))
                {
                    bottom = grid[r + 1][c];
                }
                auto right = INT_MAX;
                if (!(c + 1 >= cols))
                {
                    right = grid[r][c + 1];
                }

                auto m = std::min(bottom, right);

                if (m != INT_MAX)
                    grid[r][c] += m;
            }
        }

        return grid[0][0];
    }
};

int main(int argc, char** argv) {}
