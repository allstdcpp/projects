#include <cassert>
#include <concepts>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <utility>

namespace graphs {

enum class graph_connection_type : uint8_t
{
    directed,
    undirected
};

template <graph_connection_type type>
class graph
{
public:
    using size_type = size_t;
    explicit graph(size_type count)
        : edges_(count)
    {}

    template <typename... Ts>
    void connect(size_type p, Ts... vs)
    requires std::conjunction_v<std::is_integral<Ts>...> && (sizeof...(Ts) > 1)

    {
        (connect(p, vs), ...);
    }
    void connect(size_type p, size_type q)
    {
        edges_[p].push_back(q);

        if constexpr (type == graph_connection_type::directed)
        {
            edges_[q].push_back(p);
        }
    }
    bool connected(size_type p, size_type q) const
    {
        return std::any_of(edges_[p].begin(), edges_[p].end(), [q](auto const& e) { return e == q; });
    }
    std::vector<size_type> const& neighbors(size_type p) const { return edges_[p]; }
    size_type size() const { return edges_.size(); }
private:
    std::vector<std::vector<size_type>> edges_;
};

class dfs_path
{
public:
    using size_type = size_t;
    template <graph_connection_type type>
    dfs_path(graph<type> const& g, size_type s)
        : start_{s}
        , visited_(g.size(), false)
        , parent_(g.size())
        , size_{g.size()}
    {
        dfs<type>(g, start_);
    }
    bool has_path(size_type q) const { return visited_[q]; }

    std::vector<size_type> path(size_type q) const
    {
        std::vector<size_type> v;
        v.reserve(size_);

        if (visited_[q])
        {
            v.push_back(q);
            auto p = parent_[q];
            while (p != start_)
            {
                v.push_back(p);
                p = parent_[p];
            }
            v.push_back(start_);
            std::reverse(v.begin(), v.end());
        }
        return v;
    }


private:
    template <graph_connection_type type>
    void dfs(graph<type> const& g, size_type p)
    {
        visited_[p] = true;

        for (auto const& e : g.neighbors(p))
        {
            if (!visited_[e])
            {
                dfs(g, e);
                parent_[e] = p;
            }
        }
    }

    size_type start_{};
    std::vector<bool> visited_;
    std::vector<size_type> parent_;
    size_type size_{};
};

class bfs_path
{
public:
    using size_type = size_t;
    template <graph_connection_type type>
    bfs_path(graph<type> const& g, size_type s)
        : start_{s}
        , visited_(g.size(), false)
        , parent_(g.size())
        , size_{g.size()}
        , distance_(g.size(), 0)
    {
        bfs<type>(g);
    }
    bool has_path(size_type q) const { return visited_[q]; }

    std::vector<size_type> path(size_type q) const
    {
        std::vector<size_type> v;
        v.reserve(size_);

        if (visited_[q])
        {
            v.push_back(q);
            auto p = parent_[q];
            while (p != start_)
            {
                v.push_back(p);
                p = parent_[p];
            }
            v.push_back(start_);
            std::reverse(v.begin(), v.end());
        }
        return v;
    }

    size_type distance(size_type p) const { return distance_[p]; }

private:
    template <graph_connection_type type>
    void bfs(graph<type> const& g)
    {
        std::queue<int> q;

        q.push(start_);
        visited_[start_] = true;
        distance_[start_] = 0;

        while (!q.empty())
        {
            auto t = q.front();
            q.pop();

            for (auto const& n : g.neighbors(t))
            {
                if (!visited_[n])
                {
                    visited_[n] = true;
                    parent_[n] = t;
                    distance_[n] = distance_[t] + 1;
                    q.push(n);
                }
            }
        }
    }

    size_type start_{};
    std::vector<bool> visited_;
    std::vector<size_type> parent_;
    std::vector<size_type> distance_;
    size_type size_{};
};

} // namespace graphs

int main(int argc, char** argv)
{
    using namespace graphs;

    graph<graph_connection_type::undirected> g{13};

    g.connect(0, 6, 2, 1, 5);
    g.connect(1, 0);
    g.connect(2, 0);
    g.connect(3, 5, 4);
    g.connect(4, 5, 6, 3);
    g.connect(5, 3, 4, 0);
    g.connect(6, 0, 4);
    g.connect(7, 8);
    g.connect(8, 7);
    g.connect(9, 11, 10, 12);
    g.connect(10, 9);
    g.connect(11, 9, 12);

    bfs_path path{g, 0z};

    std::cout << "has path(0, 6): " << std::boolalpha << path.has_path(6) << std::endl;
    std::cout << "has path(0, 3): " << std::boolalpha << path.has_path(6) << std::endl;

    auto p = path.path(3);

    std::copy(p.begin(), p.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "distance path(0, 3): " << std::boolalpha << path.distance(3) << std::endl;

    return 0;
}
