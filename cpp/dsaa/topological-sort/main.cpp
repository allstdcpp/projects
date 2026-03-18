#include <cassert>
#include <iostream>
#include <stack>
#include <vector>

namespace graphs {

class graph
{
public:
    explicit graph(size_t size)
        : neighbors_(size, std::vector<int>{})
    {}

    void connect(size_t p, size_t q) { neighbors_[p].push_back(q); }
    std::vector<int> vertices() const
    {
        std::vector<int> result;
        for (auto i = 0; i < neighbors_.size(); ++i)
            result.push_back(i);

        return result;
    }
    std::vector<int> const& neighbors(size_t p) const { return neighbors_[p]; }
    size_t size() const { return neighbors_.size(); }
    bool emtpy() const { return neighbors_.size() == 0; }
private:
    std::vector<std::vector<int>> neighbors_;
};

class top_sort
{
public:
    top_sort(const graph& g)
        : visited_(g.size(), false)
    {
        for (auto e : g.vertices())
        {
            if (!visited_[e])
                dfs(g, e);
        }
    }

    std::stack<int> const& path() { return result_; }

private:

    void dfs(graph const& g, size_t index)
    {
        visited_[index] = true;

        for (auto const& e : g.neighbors(index))
        {
            if (!visited_[e])
            {
                dfs(g, e);
            }
        }
        result_.push(index);
    }

    std::vector<int> visited_;
    std::stack<int> result_;
};

} // namespace graphs

int main(int argc, char** argv)
{
    using namespace graphs;

    graph g(7);
    g.connect(0, 2);
    g.connect(0, 5);
    g.connect(0, 1);

    g.connect(1, 4);
    g.connect(5, 2);

    g.connect(3, 2);
    g.connect(3, 5);
    g.connect(3, 4);
    g.connect(3, 6);

    g.connect(6, 0);
    g.connect(6, 4);

    top_sort s{g};

    auto result = s.path();
    while (!result.empty())
    {
        std::cout << result.top() << " ";
        result.pop();
    }
    std::cout << std::endl;

    return 0;
}
