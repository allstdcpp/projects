#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename TRandomAccessIterator>
void shuffle(TRandomAccessIterator begin, TRandomAccessIterator end)
{
    for (auto current = begin; current != end; ++current)
    {
        int r = std::rand() % (std::distance(begin, current) + 1);
        auto other = begin + r;
        std::iter_swap(current, other);
    }
}

template <typename TInputIterator>
void print(TInputIterator begin, TInputIterator end)
{
    std::copy(begin, end, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<int> vs(10);

    std::iota(vs.begin(), vs.end(), 1);
    print(vs.begin(), vs.end());
    shuffle(vs.begin(), vs.end());
    print(vs.begin(), vs.end());

    return 0;
}
