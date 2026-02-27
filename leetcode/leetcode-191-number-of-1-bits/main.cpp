#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int hammingWeight(int n) {
        int x = 0;
        while(n != 0) {
            n = n & (n - 1);
            ++x;
        }
        return x;
    }
};

int main(int argc, char** argv) { return 0; }
