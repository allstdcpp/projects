#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
public:

    bool isInterleaved(std::string a, std::string b, std::string c)
    {
        if(a.size() + b.size() != c.size()) return false;

        std::unordered_map<char, int> m;

        for(auto e : a) ++m[e];
        for(auto e : b) ++m[e];
        for(auto e : c) --m[e];
        for(auto e : c) if(m[e] != 0) return false;
        return true;
    }
};

int main(int argc, char** argv)
{

    return 0;
}
