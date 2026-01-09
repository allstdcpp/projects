#include <cctype>
#include <functional>
#include <string>
#include <vector>

class Solution
{
public:
    void setZeros(std::vector<std::vector<int>>& g)
    {
        std::vector<std::vector<int>> visited(g.size());

        for (auto i = 0; i < visited.size(); ++i)
        {
            visited[i].resize(g[i].size());
        }

        std::function<void(int, int)> f = [&](int r, int c) {
            if (r < 0 || c < 0 || r >= g.size() || c >= g[r].size())
                return;

            if (visited[r][c])
                return;

            visited[r][c] = true;

            if (g[r][c] == 0)
            {
                for (auto i = 0; i < g[r].size(); ++i)
                {
                    if (g[r][i] != 0)
                        visited[r][i] = true;
                    g[r][i] = 0;
                }
                for (auto i = 0; i < g.size(); ++i)
                {
                    if (g[i][c] != 0)
                        visited[i][c] = true;
                    g[i][c] = 0;
                }
            }

            f(r - 1, c);
            f(r, c + 1);
            f(r + 1, c);
            f(r, c - 1);
        };

        for (auto i = 0; i < g.size(); ++i)
        {
            for (auto j = 0; j < g[i].size(); ++j)
            {
                f(i, j);
            }
        }
    }
};

int main(int argc, char** argv) { return 0; }
