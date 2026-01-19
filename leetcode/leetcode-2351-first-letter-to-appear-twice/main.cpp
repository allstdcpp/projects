#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
#include <vector>
#include <utility>

class Solution
{
public:

    char repeatedCharacter(std::string s)
    {
        std::array<bool, 26> seen = {false};

        for(auto c : s) {
            if(seen[c - 'a']) return c;
            seen[c - 'a'] = true;
        }

        __builtin_unreachable();
    }
};

int main(int argc, char** argv)
{
    return 0;
}
