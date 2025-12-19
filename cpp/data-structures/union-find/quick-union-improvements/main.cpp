#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

namespace datastructures {

template <typename T>
class quick_union
{
public:
    quick_union(std::size_t size);

    void connect(std::size_t p, std::size_t q);
    [[nodiscard]] bool connected(std::size_t p, std::size_t q);

private:
    std::size_t root(std::size_t n);
    std::size_t size_;
    std::vector<T> elements_;
    std::vector<size_t> weights_;
    std::size_t components_{size_};
};

template <typename T>
quick_union<T>::quick_union(std::size_t size)
    : size_{size}
    , elements_(size, 0)
    , weights_(size, 0)
{
    std::iota(elements_.begin(), elements_.end(), 0);
}

template <typename T>
void quick_union<T>::connect(std::size_t p, std::size_t q)
{
    auto pid = root(p);
    auto qid = root(q);

    if (pid == qid)
        return;

    if (weights_[pid] < weights_[qid])
    {
        elements_[pid] = qid;
        weights_[qid] += weights_[pid];
    }
    else
    {
        elements_[qid] = pid;
        weights_[pid] += weights_[qid];
    }
    --components_;
}

template <typename T>
bool quick_union<T>::connected(std::size_t p, std::size_t q)
{
    auto pid = root(p);
    auto qid = root(q);

    return pid == qid;
}

template <typename T>
std::size_t quick_union<T>::root(std::size_t n)
{
    while (n != elements_[n])
    {
        n = elements_[n];
    }
    return n;
}

} // namespace datastructures

int main(int argc, char** argv)
{
    datastructures::quick_union<int> q{4};
    q.connect(0, 1);
    q.connect(1, 2);
    q.connect(0, 2);

    std::cout << std::boolalpha << "Connected (1, 2): " << q.connected(1, 2) << std::endl;
    std::cout << std::boolalpha << "Connected (1, 3): " << q.connected(1, 3) << std::endl;
}
