#include <functional>
#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(NULL)
    {}
};
class Solution
{
public:
    bool hasCycle(ListNode* head)
    {
        ListNode* f = head;
        ListNode* s = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;
            if (s == f)
                return true;
        }
        return false;
    }
};

int main(int argc, char** argv) { return 0; }
