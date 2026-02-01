#include <string>
#include <unordered_map>

class Solution
{
public:

    bool checkInclusion(std::string s1, std::string s2)
    {
        if (s2.size() < s1.size())
            return false;

        int k = s1.size();

        std::unordered_map<char, int> freq;
        for (auto c : s1)
        {
            freq[c] += 1;
        }

        std::unordered_map<char, int> current;
        auto i = 0;

        while (i < k)
        {
            current[s2[i++]] += 1;
        }

        if (current == freq)
            return true;

        while (i < s2.size())
        {
            auto prev = s2[i - k];
            current[prev] -= 1;

            if (current[prev] == 0)
            {
                current.erase(prev);
            }
            current[s2[i]] += 1;

            if (current == freq)
                return true;
            ++i;
        }

        return false;
    }
};

int main(int argc, char** argv) { return (bool)Solution{}.checkInclusion("ab", "eidbaooo"); }
