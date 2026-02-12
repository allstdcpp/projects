#include <iostream>

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
    ListNode* reverseBetween(ListNode* head, int left, int right)
    {
        ListNode dummy;
        auto ptr = &dummy;

        auto current = head;
        auto i = 1;

        for (; i < left; ++i)
        {
            ptr->next = current;
            current = current->next;
            ptr = ptr->next;
        }

        auto last = current;
        ListNode* prev = nullptr;

        while (i <= right)
        {
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            ++i;
        }

        ptr->next = prev;
        last->next = current;

        return dummy.next;
    }
};

int main(int argc, char** argv)
{
    auto p = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    auto z = Solution{}.reverseBetween(p, 2, 4);

    return z->val;
}
