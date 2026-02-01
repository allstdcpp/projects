#include <vector>

class Solution
{
public:

    std::vector<int> getAverages(std::vector<int>& n, int k)
    {
        std::vector<int> result(n.size(), -1);

        long long windowSum = 0;
        int windowSize = 2 * k + 1;

        for (auto i = 0; i < windowSize; ++i)
        {
            windowSum += n[i];
        }

        result[windowSize / 2] = windowSum / windowSize;

        for (auto i = k + 1; i < n.size() - k; ++i)
        {
            windowSum -= n[i - k - 1];
            windowSum += n[i + k];
            result[i] = windowSum / windowSize;
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
