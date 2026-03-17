#include <functional>
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
    ListNode* deleteMiddle(ListNode* head)
    {
        auto fast = head;
        auto slow = head;
        ListNode* prev = nullptr;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            prev = slow;
            slow = slow->next;
        }

        if (prev && slow)
        {
            prev->next = slow->next;
        }
        else if (!prev)
        {
            head = nullptr;
        }

        return head;
    }
};

int main(int argc, char** argv) {}
