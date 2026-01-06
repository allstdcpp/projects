#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

namespace datastructures {

template <typename T>
class quick_find
{
public:
    quick_find(std::size_t size);

    void connect(size_t p, size_t q);
    [[nodiscard]] bool connected(size_t p, size_t q);

private:
    std::size_t size_;
    std::vector<T> elements_;
};

template <typename T>
quick_find<T>::quick_find(std::size_t size)
    : elements_(size, 0)
{
    std::iota(elements_.begin(), elements_.end(), 0);
}

template <typename T>
void quick_find<T>::connect(size_t p, size_t q)
{
    auto pid = elements_[p];
    auto qid = elements_[q];

    if (pid == qid)
        return;

    for (auto& e : elements_)
    {
        if (e == pid)
            e = qid;
    }
}

template <typename T>
bool quick_find<T>::connected(size_t p, size_t q)
{
    auto pid = elements_[p];
    auto qid = elements_[q];

    return (pid == qid);
}

} // namespace datastructures

int main(int argc, char** argv)
{
    datastructures::quick_find<int> q{4};
    q.connect(0, 1);
    q.connect(1, 2);
    q.connect(0, 2);

    std::cout << std::boolalpha << "Connected (1, 2): " << q.connected(1, 2) << std::endl;
    std::cout << std::boolalpha << "Connected (1, 3): " << q.connected(1, 3) << std::endl;
}
