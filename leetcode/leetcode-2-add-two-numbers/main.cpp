#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 */
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

    ListNode* addTwoNumbers(ListNode* a, ListNode* b)
    {
        int carry = 0;

        ListNode dummy;
        ListNode* ptr = &dummy;

        while(a && b) {
            auto sum = a->val + b->val + carry;
            carry = sum / 10;

            ptr->next = new ListNode(sum % 10);
            ptr = ptr->next;

            a = a->next;
            b = b->next;
        }

        while(a) {
            auto sum = a->val + carry;
            carry = sum / 10;

            ptr->next = new ListNode(sum % 10);
            ptr = ptr->next;
            a = a->next;
        }

        while(b) {
            auto sum = b->val + carry;
            carry = sum / 10;

            ptr->next = new ListNode(sum % 10);
            ptr = ptr->next;
            b = b->next;
        }

        if(carry > 0) {
            ptr->next = new ListNode(carry);
        }

        return dummy.next;
    }
};

int main(int argc, char** argv) { return 0; }
