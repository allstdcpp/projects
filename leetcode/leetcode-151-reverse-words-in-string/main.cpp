#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Solution
{
public:
    std::string reverseWords(std::string s)
    {
        std::vector<std::string> v;

        int left = 0;
        int right = 0;

        while (true)
        {
            left = right;
            while (left < s.size() && s[left] == ' ')
                ++left; // eat space
            if (left >= s.size())
                break;
            right = left + 1;
            while (right < s.size() && s[right] != ' ')
                ++right;
            auto diff = right - left;
            if (left + diff >= s.size())
            {
                v.push_back(s.substr(left, std::string::npos));
                break;
            }
            else
                v.push_back(s.substr(left, diff));
        }

        std::reverse(v.begin(), v.end());
        std::string result;

        result.append(v[0]);

        for (auto i = 1; i < v.size(); ++i)
        {
            result.push_back(' ');
            result.append(v[i]);
        }

        return result;
    }
};

int main(int argc, char** argv)
{
    auto r = Solution{}.reverseWords("the sky is blue");
    std::cout << r << std::endl;
    return 0;
}
