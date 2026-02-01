#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

class Solution
{
public:
    int appendCharacters(std::string s, std::string t)
    {
        int total = 0;
        int i = 0;
        int j = 0;

        while(i < t.size()) {
            if(t[i] == s[j++]) {
                ++i;
                break;
            }
        }

        return total;
    }
};

int main(int argc, char** argv) {}
