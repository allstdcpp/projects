#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

template <typename T>
void selection_sort(std::vector<T>& input)
{
    for (auto i = 0; i < input.size(); ++i)
    {
        auto min = i;

        for(auto j = i + 1; j < input.size(); ++j) {
            if(input[j] < input[min]) min = j;
        }

        std::swap(input[min], input[i]);
    }
}

int main(int argc, char** argv)
{
    std::vector<int> vs{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    selection_sort(vs);
    std::copy(vs.begin(), vs.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
