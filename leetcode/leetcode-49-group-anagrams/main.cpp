#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<std::string>> twoSum(std::vector<std::string>& n)
    {
        std::map<std::string, std::vector<std::string>> m;

        for (auto const& s : n)
        {
            auto sorted = s;
            std::sort(sorted.begin(), sorted.end());

            auto [it, succ] = m.insert(std::pair{sorted, std::vector{s}});
            if (!succ)
                it->second.push_back(s);
        }

        std::vector<std::vector<std::string>> result;
        result.reserve(m.size());

        for (auto const& kvp : m)
        {
            result.push_back(kvp.second);
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
