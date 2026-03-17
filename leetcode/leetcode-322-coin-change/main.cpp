#include <climits>
#include <functional>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    struct pair_hasher
    {
        size_t operator()(std::pair<int, int> const& p) const { return p.first + p.second; }
    };
    int coinChange(std::vector<int>& coins, int amount)
    {
        std::unordered_map<std::pair<int, int>, int, pair_hasher> m;

        int min = LONG_MAX;

        std::function<void(int, int, int)> f = [&m, &f, &min, &coins, &amount](int c, int current, int total) {
            if (current > total)
                return -1;

            if (current == total)
            {
                return c;
            }

            for (auto coin : coins)
            {
                auto max = INT_MAX - current;
                if (coin > max)
                    continue;

                auto remainder = total - (current + coin);

                if (m.count(std::pair{remainder, coin}))
                {
                    min = std::min(min, 1 + m[std::pair{remainder, coin}]);
                }
                else
                {
                    f(c + 1, current + coin, total);
                }
            }
        };

        f(0, 0, amount);

        if (min != INT_MAX)
            return min;
        return -1;
    }
};

int main(int argc, char** argv) { return 0; }
