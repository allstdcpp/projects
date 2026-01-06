#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
void insertion_sort(std::vector<T>& input)
{
    for (auto i = 0; i < input.size(); ++i)
    {
        for (auto j = i; j > 0; --j)
        {
            if (input[j] < input[j - 1])
                std::swap(input[j], input[j - 1]);
            else
                break;
        }
    }
}

int main(int argc, char** argv)
{
    std::vector<int> vs{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    insertion_sort(vs);
    std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
