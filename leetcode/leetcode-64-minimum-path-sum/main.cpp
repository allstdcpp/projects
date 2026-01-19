#include <functional>
#include <iostream>
#include <vector>

class Solution
{
public:
    int minPathSum(std::vector<std::vector<int>>& g)
    {
        int min = 201;

        int rows = g.size();

        std::function<void(int, int, int)> f = [&](int r, int c, int sum) {
            if (r < 0 || r >= rows || c < 0 || c >= g[r].size())
                return;

            if (g[r][c] < 0)
                return;

            auto total = sum + g[r][c];
            auto temp = g[r][c];
            g[r][c] = -1;

            if (r == rows - 1 && c == g[rows - 1].size() - 1)
            {
                min = std::min(min, total);
            }
            else
            {
                f(r + 1, c, total);
                f(r, c + 1, total);
            }
            g[r][c] = temp;
        };

        f(0, 0, 0);
        return min;
    }
};

int main(int argc, char** argv)
{
    std::vector vs{std::vector{1, 2, 3}, std::vector{4, 5, 6}};
    std::cout << (Solution{}.minPathSum(vs)) << std::endl;
    return 0;
}
