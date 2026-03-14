#include <functional>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string reversePrefix(std::string s, int k) {
        std::reverse(s.begin(), s.begin() + k); 
        return s;
    }
};


int main(int argc, char** argv) {}
