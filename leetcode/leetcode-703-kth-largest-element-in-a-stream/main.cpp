#include <iostream>
#include <queue>
#include <vector>

class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums)
        : k_{k}
     {
        for(auto e : nums)
            add(e);
    }
    
    int add(int val) {
        q_.push(val);

        if(q_.size() > k_)
            q_.pop();

        return q_.top();
    }

private:
    int k_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q_;
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

int main(int argc, char** argv) { return 0; }
