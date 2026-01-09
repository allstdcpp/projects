#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<int>> allPathsSourceTarget(std::vector<std::vector<int>>& g)
    {
        std::vector<std::vector<int>> vs;
        std::vector<bool> visited(g.size(), false);
        std::vector<int> current;

        std::function<void(int)> f = [&](int vertex) {
            if (vertex == g.size() - 1)
            {
                current.push_back(vertex);
                vs.push_back(current);
                current.pop_back();
                return;
            }

            visited[vertex] = true;
            current.push_back(vertex);

            auto const& neighbours = g[vertex];

            for (auto n : neighbours)
            {
                if (visited[n])
                    continue;

                f(n);
            }
            visited[vertex] = false;
            current.pop_back();
        };

        f(0);

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
