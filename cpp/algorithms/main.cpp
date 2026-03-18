#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

template <typename TTag>
struct dispatch;

template <typename T>
auto greater_than(T&& value)
{
    return [v = std::forward<T>(value)](auto const& z) { return z > v; };
}

template <typename T>
auto greater_than_eq(T&& value)
{
    return [v = std::forward<T>(value)](auto const& z) { return z >= v; };
}

template <typename T>
auto less_than(T&& value)
{
    return [v = std::forward<T>(value)](auto const& z) { return z < v; };
}

template <typename T>
auto less_than_eq(T&& value)
{
    return [v = std::forward<T>(value)](auto const& z) { return z <= v; };
}

template <typename T>
auto equal(T&& value)
{
    return [v = std::forward<T>(value)](auto const& z) { return z == v; };
}

template <>
struct dispatch<struct search_operations_tag>
{
    static void apply()
    {
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};
            std::cout << "All of vs greater than zero: " << std::boolalpha
                      << std::all_of(vs.begin(), vs.end(), greater_than(0)) << std::endl;

            std::cout << "All of vs less than zero: " << std::boolalpha
                      << std::all_of(vs.begin(), vs.end(), less_than(0)) << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};
            std::cout << "Any of vs greater than zero: " << std::boolalpha
                      << std::any_of(vs.begin(), vs.end(), greater_than(0)) << std::endl;

            std::cout << "Any of vs less than zero: " << std::boolalpha
                      << std::any_of(vs.begin(), vs.end(), less_than(0)) << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};
            std::cout << "None of vs greater than zero: " << std::boolalpha
                      << std::none_of(vs.begin(), vs.end(), greater_than(0)) << std::endl;

            std::cout << "None of vs less than zero: " << std::boolalpha
                      << std::none_of(vs.begin(), vs.end(), less_than(0)) << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};

            {
                auto it = std::find(vs.begin(), vs.end(), 3);
                std::cout << "Find result: " << *it << std::endl;
            }
            {
                auto it = std::find(vs.begin(), vs.end(), 30);
                if (it == std::end(vs))
                {
                    std::cout << "Element not found...\n";
                }
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};

            {
                auto it = std::find_if(vs.begin(), vs.end(), equal(3));
                std::cout << "Find if result: " << *it << std::endl;
            }
            {
                auto it = std::find_if(vs.begin(), vs.end(), equal(30));
                if (it == std::end(vs))
                {
                    std::cout << "Element not found...\n";
                }
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};

            {
                auto it = std::find_if_not(vs.begin(), vs.end(), equal(1));
                std::cout << "Find if not result: " << *it << std::endl;
            }
            {
                auto it = std::find_if_not(vs.begin(), vs.end(), equal(30));
                std::cout << "Find if not result: " << *it << std::endl;
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6};

            {
                std::vector<int> ts{5, 6};

                auto it = std::find_first_of(vs.begin(), vs.end(), ts.begin(), ts.end());
                std::cout << "Find first of: " << *it << std::endl;
            }
            {
                std::vector<int> ts{50, 60};

                auto it = std::find_first_of(vs.begin(), vs.end(), ts.begin(), ts.end());

                if (it == std::end(vs))
                {
                    std::cout << "Element not found..." << std::endl;
                }
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 40, 50, 60};

            auto difference = [](int a, int b) { return std::abs(a - b) == 10; };

            {
                auto it = std::adjacent_find(vs.begin(), vs.end(), difference);
                while (it != std::end(vs))
                {
                    std::cout << "Find if result: " << *it << std::endl;
                    it = std::adjacent_find(std::next(it), vs.end(), difference);
                }
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 40, 50, 60};

            {
                std::cout << "count of 3: " << (std::count(vs.begin(), vs.end(), 3)) << std::endl;
                std::cout << "count of elements greater than 40: "
                          << (std::count_if(vs.begin(), vs.end(), greater_than(40))) << std::endl;
            }
        }
        {
            std::vector<int> vs{1, 2, 3, 40, 50, 60};
            std::vector<int> ys{1, 2, 3};

            {
                auto eq = std::equal(vs.begin(), vs.end(), ys.begin(), ys.end());

                std::cout << "Are equal: " << std::boolalpha << eq << std::endl;

                eq = std::equal(ys.begin(), ys.end(), vs.begin());

                std::cout << "Are equal: " << std::boolalpha << eq << std::endl;
            }
        }
    }
};

template <>
struct dispatch<struct copy_operations_tag>
{
    static void apply()
    {
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            std::vector<int> us;

            std::copy_if(vs.begin(), vs.end(), std::back_inserter(us), [](auto v) { return v % 2 == 0; });

            std::copy(us.begin(), us.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            std::vector<int> us;

            std::copy_n(vs.begin(), 4, std::back_inserter(us));

            std::copy(us.begin(), us.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }
};

template <>
struct dispatch<struct transformation_operations_tag>
{
    static void apply()
    {
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            std::vector<int> us;

            std::transform(vs.begin(), vs.end(), std::back_inserter(us), [](auto x) { return x * 10; });

            std::copy(us.begin(), us.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            std::replace(vs.begin(), vs.end(), 10, 100);

            std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        {
            std::vector<int> vs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            std::replace_if(vs.begin(), vs.end(), less_than(5), 100);

            std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }
};

template <>
struct dispatch<struct generation_operations_tag>
{
    static void apply()
    {
        {
            std::vector<int> vs;
            vs.resize(10);

            std::fill(vs.begin(), vs.end(), 100);

            std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        {
            std::vector<int> vs;
            vs.resize(10);

            std::fill_n(vs.begin(), 3, 100);

            std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
        {
            std::vector<int> vs;
            vs.resize(10);

            int c = 0;
            std::generate(vs.begin(), vs.end(), [&c] { return ++c; });

            std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
    }
};

int main(int argc, char** argv)
{
    dispatch<struct generation_operations_tag>::apply();
    return 0;
}
