#include <cassert>
#include <string>
#include <unordered_set>

class Solution
{
public:
    int lengthOfLongestSubstring(std::string const& s)
    {
        int longest{};
        auto i = 0;
        auto j = 0;

        std::unordered_set<int> set;

        while (j < s.size())
        {
            auto [_, succ] = set.insert(s[j]);
            if (succ)
            {
                longest = std::max(longest, (j - i) + 1);
                ++j;
                continue;
            }
            while (i < j && s[i] != s[j])
            {
                set.erase(s[i++]);
            }
            set.erase(s[i++]);
        }

        return longest;
    }
};

int main(int argc, char** argv) {
    return Solution{}.lengthOfLongestSubstring("abcabccbb");
}

