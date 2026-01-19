#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    int numMatchingSubseq(std::string s, std::vector<std::string>& words)
    {
        auto fx = [&s](std::string const& input) -> bool {
            size_t i = 0;
            size_t j = 0;

            while (i < input.size())
            {
                while (j < s.size())
                {
                    if (input[i] == s[j++])
                    {
                        ++i;
                        break;
                    }
                }

                if (j == s.size())
                    break;
            }
            if (i == input.size())
                return true;
            return false;
        };

        std::unordered_map<std::string, int> count;
        std::unordered_map<std::string, bool> matches;

        for (auto const& word : words)
        {
            count[word] += 1;

            if (count[word] == 1)
            {
                matches[word] = fx(word);
            }
        }

        int total = 0;
        for (auto const& w : matches)
        {
            if (w.second)
            {
                total += count[w.first];
            }
        }
        return total;
    }
};

int main(int argc, char** argv) {}
