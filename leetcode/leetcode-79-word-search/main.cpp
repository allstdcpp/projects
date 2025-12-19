#include <cctype>
#include <functional>
#include <string>
#include <vector>

class Solution
{
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        bool match = false;
        std::function<void(int, int, int)> dfs = [&](int row, int col, int index) {
            if (index > word.size())
                return;

            if (index == word.size())
            {
                match = true;
                return;
            }

            if (row < 0 || row >= board.size())
            {
                return;
            }
            if (col < 0 || col >= board[row].size())
            {
                return;
            }

            if (board[row][col] == '.')
                return;
            if (board[row][col] == word[index])
            {
                auto temp = board[row][col];
                board[row][col] = '.';
                dfs(row, col + 1, index + 1); // right
                dfs(row + 1, col, index + 1); // up
                dfs(row, col - 1, index + 1); // left
                dfs(row - 1, col, index + 1); // down
                // restore
                board[row][col] = temp;
            }
        };

        for (size_t i = 0; i < board.size(); ++i)
        {
            for (size_t j = 0; j < board[i].size(); ++j)
            {
                dfs(i, j, 0);
                if (match)
                    return true;
            }
        }

        return false;
    }
};

int main(int argc, char** argv) {}
