#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

class NumArray
{
public:
    NumArray(std::vector<int>& nums)
        : data_(nums.size(), 0)
    {
        construct();
    }

    void update(int index, int val) {}

    int sumRange(int left, int right) {}

private:

    void construct() {}

    int clear_right_most_1_bit(int n) { return n & (-n); }

    std::vector<int> data_;
};

int main(int argc, char** argv) {}
