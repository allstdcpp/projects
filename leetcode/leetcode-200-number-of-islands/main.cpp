#include <functional>
#include <vector>

class Solution
{
public:
    int numIslands(std::vector<std::vector<char>>& grid)
    {
        using size_type = decltype(grid.size());
        std::vector<std::vector<bool>> visited(grid.size());
        for (size_type i = 0; i < grid.size(); ++i)
        {
            visited[i].resize(grid[i].size(), false);
        }
        int components{};

        std::function<void(int, int)> dfs = [&](int row, int col) {
            if (row >= grid.size() || row < 0)
                return;
            if (col >= grid[row].size() || col < 0)
                return;

            if (visited[row][col])
                return;
            visited[row][col] = true;

            if (grid[row][col] == '0')
                return;

            dfs(row, col - 1); // left
            dfs(row, col + 1); // right
            dfs(row - 1, col); // up
            dfs(row + 1, col); // down
        };

        for (size_type i = 0; i < grid.size(); ++i)
        {
            for (size_type j = 0; j < grid[i].size(); ++j)
            {
                if (visited[i][j] || grid[i][j] == '0')
                    continue;
                dfs(i, j);
                ++components;
            }
        }

        return components;
    }
};

int main(int argc, char** argv) {}
