#include <functional>
#include <unordered_set>
#include <vector>

class Solution
{
public:

    template <typename T, typename U>
    class pair_hasher
    {
    public:
        size_t operator()(std::pair<T, U> const& p) const noexcept { return p.first + p.second ^ 13; }
    };

    bool checkValid(std::vector<std::vector<int>>& matrix)
    {
        std::unordered_set<std::pair<int, int>, pair_hasher<int, int>> row;
        std::unordered_set<std::pair<int, int>, pair_hasher<int, int>> col;

        for (decltype(matrix.size()) i = 0; i < matrix.size(); ++i)
        {
            for (decltype(matrix.size()) j = 0; j < matrix[i].size(); ++j)
            {
                if (!row.emplace(i, matrix[i][j]).second || !col.emplace(j, matrix[i][j]).second)
                    return false;
            }
        }

        return true;
    }
};

int main(int argc, char** argv) {}
