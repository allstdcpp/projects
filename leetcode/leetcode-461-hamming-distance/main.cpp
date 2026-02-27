#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int hammingDistance(int x, int y) {
        auto v = x ^ y;
        x = 0;
        while(v != 0) {
            v = v & (v - 1);
            ++x;
        }
        return x;
    }
};

int main(int argc, char** argv) { return 0; }
