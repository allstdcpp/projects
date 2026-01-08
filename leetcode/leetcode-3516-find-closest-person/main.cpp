#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

class Solution
{
public:

    int findCloset(int x, int y, int z) {
        if(auto v = (std::abs(z - x) < std::abs(z - y)); v) {
            return 1;
        }else if(auto v = (std::abs(z - x) > std::abs(z - y)); v) {
            return 2;
        }else{
            return 0;
        }
    }
};

int main(int argc, char** argv) { return 0; }
