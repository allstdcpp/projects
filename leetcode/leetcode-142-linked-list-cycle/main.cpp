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
    ListNode* detectCycle(ListNode* head)
    {
        ListNode* f = head;
        ListNode* s = head;

        while (f && f->next)
        {
            s = s->next;
            f = f->next->next;
            if (s == f)
            {
                auto k = head;
                while (k != s)
                {
                    s = s->next;
                    k = k->next;
                }
                return k;
            }
        }
        return nullptr;
    }
};

int main(int argc, char** argv) { return 0; }
