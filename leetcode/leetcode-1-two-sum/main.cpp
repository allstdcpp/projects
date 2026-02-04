#include <iostream>
#include <unordered_map>
#include <vector>

class Solution
{
public:

    std::vector<int> twoSum(std::vector<int>& n, int t)
    {
        std::vector<int> result(2, 0);

        std::unordered_map<int, int> indices;

        for (auto i = 0; i < n.size(); ++i)
        {
            auto missing = t - n[i];
            auto it = indices.find(missing);
            if (it == indices.end())
            {
                indices.insert(std::pair{n[i], i});
            }
            else
            {
                result[0] = it->second;
                result[1] = i;
            }
        }

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
