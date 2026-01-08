#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <vector>

class Solution
{
public:

    std::vector<std::string> generateParentheses(int n)
    {
        std::vector<std::string> results;

        std::string current;
        std::vector<char> chars{'(', ')'};
        std::stack<char> s;

        std::function<void()> f = [&]() {
            if (current.size() == n * 2)
            {
                if (s.empty())
                    results.push_back(current);
                return;
            }

            for (auto c : chars)
            {
                if (c == '(')
                {
                    current.push_back(c);
                    s.push(c);

                    f();
                    current.pop_back();
                    s.pop();
                }
                else
                {
                    if (!s.empty() && s.top() == '(')
                    {
                        current.push_back(c);
                        s.pop();
                        f();
                        s.push('(');
                        current.pop_back();
                    }
                }
            }
        };

        f();

        return results;
    }
};

int main(int argc, char** argv)
{
    auto v = Solution{}.generateParentheses(3);

    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}
