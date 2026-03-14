#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class Solution {
public:
    int subarraySum(vector<int>& nums) {
        auto v = nums;
        auto p = nums;
        std::partial_sum(nums.begin(), nums.end(), p.begin());

        for(int i = 0; i < nums.size(); ++i) {
            int s = std::max(0, i - nums[i]);
            int l = s - 1;
            int r = i;
            int to = p[r];
            int from = (l < 0) ? 0 : p[l];
            int val = to - from;
            v[i] = val;
        }

        return std::accumulate(v.begin(), v.end(),0);

    }
};


int main(int argc, char** argv) {}
