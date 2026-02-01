#include <limits>
#include <vector>

class Solution
{
public:

    double findMaxAverage(std::vector<int>& nums, int k)
    {
        double current = 0.0;

        for (int i = 0; i < k; ++i)
        {
            current += nums[i];
        }
        double avg = current / k;

        for (auto i = k; i < nums.size(); ++i)
        {
            current += nums[i];
            current -= nums[i - k];
            avg = std::max(avg, (current / k));
        }

        return avg;
    }
};

int main(int argc, char** argv) { return 0; }
