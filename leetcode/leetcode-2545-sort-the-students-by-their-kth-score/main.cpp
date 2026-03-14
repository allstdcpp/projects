#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    std::vector<std::vector<int>> sortTheStudents(std::vector<std::vector<int>>& score, int k)
    {
        std::sort(score.begin(), score.end(), [k](std::vector<int>& a, std::vector<int>& b) { return a[k] > b[k]; });

        return score;
    }
};

int main(int argc, char** argv) {}
