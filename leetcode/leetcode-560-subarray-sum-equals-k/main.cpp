#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    int subarraySum(std::vector<int>& n, int k)
    {
        int left = 0;
        int current = n[left];
        int total = 0;

        if (current == k)
            ++total;

        int right = 1;

        while (right < n.size())
        {
            current += n[right];
            if (current == k)
            {
                ++total;
                ++right;
            }
            else if (current > k)
            {
                current -= n[left++];
            }
            else
            {
                ++right;
            }
        }

        return total;
    }
};

int main(int argc, char** argv) { return 0; }
