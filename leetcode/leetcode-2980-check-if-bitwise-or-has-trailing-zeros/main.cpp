#include <functional>
#include <vector>

class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        auto n = std::accumulate(nums.begin(), nums.end(), 0, [](auto a, auto b){
            return a + (b & 1 ^ 1);
        });

        return n >= 2;
    }
};


int main(int argc, char** argv) {}
