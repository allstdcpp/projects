#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    std::vector<int> findAnagrams(std::string s, std::string p)
    {
        std::vector<int> result;

        if (s.size() < p.size())
            return result;

        int k = p.size();

        std::unordered_map<char, int> freq;
        for (auto c : p)
        {
            freq[c] += 1;
        }

        std::unordered_map<char, int> current;
        auto i = 0;

        while (i < k)
        {
            current[s[i++]] += 1;
        }

        if (current == freq)
            result.push_back(0);

        while (i < s.size())
        {
            auto prev = s[i - k];
            current[prev] -= 1;

            if (current[prev] == 0)
            {
                current.erase(prev);
            }
            current[s[i]] += 1;

            if (current == freq)
                result.push_back(i - k + 1);
            ++i;
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
