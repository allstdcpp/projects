#include <iostream>
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
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode* prev = nullptr;
        ListNode* fast = head;
        ListNode* slow = head;

        int max = n;
        int i = 0;

        while (i < max && fast)
        {
            fast = fast->next;
            ++i;
        }

        while (fast)
        {
            fast = fast->next;
            prev = slow;
            slow = slow->next;
        }

        if (prev && slow)
        {
            prev->next = slow->next;
        }
        else if (!prev && slow)
        {
            head = slow->next;
        }
        else if (!prev)
        {
            head = nullptr;
        }

        return head;
    }
};

int main(int argc, char** argv) { return 0; }
