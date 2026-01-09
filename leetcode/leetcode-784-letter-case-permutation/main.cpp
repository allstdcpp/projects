#include <algorithm>
#include <array>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class Solution
{
public:

    std::vector<std::string> letterCasePermutation(std::string s)
    {
        std::vector<std::string> vs;

        std::array<std::function<char(char)>, 2> fs{
            [](char c) { return std::tolower(c); }, [](char c) { return std::toupper(c); }};

        std::function<void(std::string&, int)> f = [&](std::string& current, int i) {
            if (s.size() == current.size())
            {
                vs.push_back(current);
                return;
            }

            auto t = s[i];
            if (t != '.' && !std::isdigit(t))
            {
                for (auto fun : fs)
                {
                    s[i] = '.';
                    current.push_back(fun(t));
                    f(current, i + 1);
                    current.pop_back();
                    s[i] = t;
                }
            }
            else if (t != '.' && std::isdigit(t))
            {
                s[i] = '.';
                current.push_back(t);
                f(current, i + 1);
                current.pop_back();
                s[i] = t;
            }
        };

        std::string current;
        current.reserve(s.size());
        f(current, 0);

        return vs;
    }
};

int main(int argc, char** argv)
{
    Solution s{};
    auto vs = s.letterCasePermutation("a1b2");

    std::copy(vs.begin(), vs.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
