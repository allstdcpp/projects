#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:

    std::vector<std::string> validStrings(int n)
    {
        std::vector<std::string> vs;
        std::array<char, 2> choices{'0', '1'};

        std::function<void(std::string&, int)> f = [&](std::string& current, int i) {
            if (current.size() == n)
            {
                vs.push_back(current);
                return;
            }

            for (auto c : choices)
            {
                if (current.size() >= 1)
                {
                    if (current.back() == '0' && c == '0')
                        continue;
                }
                current.push_back(c);
                f(current, i + 1);
                current.pop_back();
            }
        };

        std::string current;
        current.reserve(n);
        f(current, 0);

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
