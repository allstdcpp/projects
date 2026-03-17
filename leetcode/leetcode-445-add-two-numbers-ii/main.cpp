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

    ListNode* reverse(ListNode* n)
    {
        ListNode* prev = nullptr;

        auto current = n;

        while (current)
        {
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        return prev;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        auto a = reverse(l1);
        auto b = reverse(l2);

        auto carry = 0;

        ListNode* head = nullptr;

        auto l = a;
        auto r = b;

        while (l && r)
        {
            auto sum = l->val + r->val + carry;
            carry = sum / 10;
            auto v = sum % 10;
            head = new ListNode(v, head);
            l = l->next;
            r = r->next;
        }

        while (l)
        {
            auto sum = l->val + carry;
            carry = sum / 10;
            auto v = sum % 10;
            head = new ListNode(v, head);

            l = l->next;
        }

        while (r)
        {
            auto sum = r->val + carry;
            carry = sum / 10;
            auto v = sum % 10;
            head = new ListNode(v, head);

            r = r->next;
        }

        if (carry)
            head = new ListNode(carry, head);

        return head;
    }
};

int main(int argc, char** argv) {}
