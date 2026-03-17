#include <functional>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    struct pair_hash
    {
        size_t operator()(std::pair<int, int> const& p) const { return p.first + p.second; }
    };

    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) 
    {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        std::unordered_map<std::pair<int, int>, int, pair_hash> map;

        std::function<int(int, int)> f = [&obstacleGrid, m, n, &map, &f](int r, int c) {
            if (r >= m || c >= n || obstacleGrid[r][c] == 1)
            {
                return 0;
            }
            if (r == m - 1 && c == n - 1)
            {
                return 1;
            }

            auto x = map.find(std::pair<int, int>(r, c));
            if (x != std::end(map))
            {
                return x->second;
            }

            auto a = f(r + 1, c);
            auto b = f(r, c + 1);

            auto ret = a + b;
            map.insert(std::pair<std::pair<int, int>, int>{std::pair{r, c}, ret});

            return ret;
        };

        return f(0, 0);
    }
};

int main(int argc, char** argv) {}
