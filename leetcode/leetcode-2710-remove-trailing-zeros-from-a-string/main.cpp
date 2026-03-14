#include <functional>
#include <string>


class Solution {
public:
    std::string removeTrailingZeros(std::string num) {

        int i = num.size() - 1;
        for(; i >= 0; --i) {
            if(num[i] != '0') break;
        }

        if(i + 1 < num.size())
            num.erase(i + 1, std::string::npos);

        return num;
    }
};
int main(int argc, char** argv) {}
