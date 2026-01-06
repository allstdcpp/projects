#include <algorithm>
#include <vector>

namespace algo {

namespace detail {
template <typename T>
constexpr void merge(std::vector<T>& v, std::vector<T>& aux, int lo, int mid, int hi)
{
    std::copy(v.begin() + lo, v.begin() + hi + 1, aux.begin() + lo);

    auto i = lo;
    auto j = mid + 1;

    for (auto k = lo; k <= hi; ++k)
    {
        if (i > mid)
        {
            v[k] = aux[j++];
        }
        else if (j > hi)
        {
            v[k] = aux[i++];
        }
        else if (aux[i] <= aux[j])
        {
            v[k] = aux[i++];
        }
        else
        {
            v[k] = aux[j++];
        }
    }
}

template <typename T>
constexpr void merge_sort(std::vector<T>& v, std::vector<T>& aux, int lo, int hi)
{
    if (lo >= hi)
        return;

    auto mid = lo + (hi - lo) / 2;

    merge_sort(v, aux, lo, mid);
    merge_sort(v, aux, mid + 1, hi);

    merge(v, aux, lo, mid, hi);
}

} // namespace detail

template <typename T>
constexpr void merge_sort(std::vector<T>& v)
{
    auto aux = v;
    if(v.empty()) return;

    detail::merge_sort(v, aux, 0, v.size() - 1);
}

} // namespace algo
  //
namespace test {

    static constexpr bool test() {
        std::vector<int> vs{10,9,8,7,6,6,5,4,3,2,1};
        algo::merge_sort(vs);

        return std::is_sorted(vs.begin(), vs.end());
        
    }
}

int main(int argc, char** argv) { 

    static constexpr auto test_result = test::test();
    static_assert(test_result);

    return 0; 
}
