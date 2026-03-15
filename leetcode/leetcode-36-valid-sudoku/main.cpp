#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

class Solution
{
public:

    class pair_hasher
    {
    public:
        size_t operator()(std::pair<int, int> const& v) const { return v.first + v.second ^ 13; }
    };

    class tuple_hasher
    {
    public:
        size_t operator()(std::tuple<int, int, int> const& v) const
        {
            return std::get<0>(v) + std::get<1>(v) + std::get<2>(v) ^ 13;
        }
    };

    bool isValidSudoku(std::vector<std::vector<char>>& board)
    {
        std::unordered_set<std::pair<int, int>, pair_hasher> rows;
        std::unordered_set<std::pair<int, int>, pair_hasher> cols;
        std::unordered_set<std::tuple<int, int, int>, tuple_hasher> section;

        for (auto i = 0; i < board.size(); ++i)
        {
            for (auto j = 0; j < board.size(); ++j)
            {
                auto section_row = i / 3;
                auto section_col = j / 3;

                {
                    auto v = board[i][j];
                    if (v == '.')
                        continue;

                    auto x = v - '0';
                    if (!rows.insert(std::pair<int, int>{i, x}).second)
                    {
                        return false;
                    }

                    if (!cols.insert(std::pair<int, int>{j, x}).second)
                    {
                        return false;
                    }

                    if (!section.insert(std::make_tuple(section_row, section_col, x)).second)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};

int main(int argc, char** argv) {}
