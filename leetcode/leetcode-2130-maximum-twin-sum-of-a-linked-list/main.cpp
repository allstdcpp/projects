#include <functional>
#include <unordered_map>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode* next;
    ListNode()
        : val(0)
        , next(nullptr)
    {}
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {}
    ListNode(int x, ListNode* next)
        : val(x)
        , next(next)
    {}
};
class Solution
{
public:
    int pairSum(ListNode* head)
    {
        std::unordered_map<int, int> m;
        int max = 0;

        int i = 0;
        for (auto current = head; current; current = current->next, ++i)
        {
            m[i] = current->val;
        }
        int j = 0;
        for (auto current = head; current; current = current->next, ++j)
        {
            if (j <= (i / 2) - 1)
            {
                auto sum = m[(i - 1 - j) / 2] + m[j];
                max = std::max(max, sum);
            }
        }
        return max;
    }
};

int main(int argc, char** argv) {}
