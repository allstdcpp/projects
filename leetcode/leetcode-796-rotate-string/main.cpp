#include <algorithm>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    bool rotateString(std::string s, std::string g)
    {
        if(s.size() != g.size()) return false;
        if(s == g) return true;

        std::unordered_map<char, int> a;
        std::unordered_map<char, int> b;

        for(auto c : s) {
            a[c] += 1;
        }
        for(auto c : g) {
            b[c] += 1;
        }
        if(a != b) return false;

        for(auto i = 1; i < s.size(); ++i) {
            std::string t = s;
            std::reverse(t.begin(), t.end());
            std::reverse(t.begin(), t.begin() + i);
            std::reverse(t.begin() + i, t.end());

            if(t == g) return true;
        }
        return false;
    }
};

int main(int argc, char** argv) {}
