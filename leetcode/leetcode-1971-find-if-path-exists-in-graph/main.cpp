#include <functional>
#include <numeric>
#include <vector>

class Solution
{
public:
    bool validPath(int n, std::vector<std::vector<int>>& edges, int source, int dest)
    {
        std::vector<int> components_(n);
        std::vector<int> size(n, 1);
        std::iota(components_.begin(), components_.end(), 0);

        auto parent = [&](int p) {
            while (components_[p] != p)
            {
                p = components_[p];
            }
            return p;
        };

        auto connect = [&](int p, int q) {
            auto ppid = parent(p);
            auto qpid = parent(q);

            if (ppid == qpid)
                return;

            if (size[ppid] <= size[qpid])
            {
                size[qpid] += size[ppid];
                components_[ppid] = qpid;
            }
            else
            {
                size[ppid] += size[qpid];
                components_[qpid] = ppid;
            }
        };

        auto connected = [&](int p, int q) { return parent(p) == parent(q); };

        for (auto const& edge : edges)
        {
            connect(edge[0], edge[1]);
        }

        return connected(source, dest);
    }
};

int main(int argc, char** argv) {}
