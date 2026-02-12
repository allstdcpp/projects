#include <functional>
#include <iostream>
#include <iterator>
#include <stack>
#include <string>
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
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* prev = nullptr;
        ListNode* current = head;

        while (current)
        {
            auto stop = current;
            auto last = current;

            auto i = 0;

            while (i < k)
            {
                if (!stop)
                {
                    break;
                }
                last = stop;
                stop = stop->next;
                ++i;
            }

            if (i == k) // got a k group
            {
                while (current && current != stop)
                {
                    auto next = current->next;
                    current->next = prev;
                    prev = current;
                    current = next;
                }
            }
            else
            {}
        }
    }
};

int main(int argc, char** argv) { return 0; }
