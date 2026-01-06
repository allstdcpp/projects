#include <iostream>
#include <stdexcept>
#include <vector>

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:

    std::vector<std::vector<int>> spiralOrder(int m, int n, ListNode* head)
    {
        std::vector<std::vector<int>> results(m, std::vector<int>(n, -1));

        int top = 0;
        int left = 0;
        int right = n - 1;
        int bottom = m - 1;

        int direction = 2;

        while (head && top <= bottom && left <= right)
        {
            if (direction == 2) // right
            {
                for (auto i = left; head && i <= right; ++i)
                {
                    results[top][i] = head->val;
                    head = head->next;
                }
                direction = (direction + 1) % 4;
                ++top;
            }
            else if (direction == 3) // down
            {
                for (auto i = top; head && i <= bottom; ++i)
                {
                    results[i][right] = head->val;
                    head = head->next;
                }
                direction = (direction + 1) % 4;
                --right;
            }
            else if (direction == 0) // left
            {
                for (auto i = right; head && i >= left; --i)
                {
                    results[bottom][i] = head->val;
                    head = head->next;
                }
                direction = (direction + 1) % 4;
                --bottom;
            }
            else if (direction == 1) // up
            {
                for (auto i = bottom; head && i >= top; --i)
                {
                    results[i][left] = head->val;
                    head = head->next;
                }
                direction = (direction + 1) % 4;
                ++left;
            }
            else
            {
                throw std::logic_error("Invalid case.");
            }
        }

        return results;
    }
};

int main(int argc, char** argv) {}
