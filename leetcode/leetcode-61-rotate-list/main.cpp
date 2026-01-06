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
    ListNode* rotateRight(ListNode* head, int k) {

        auto size = 0;
        auto current = head;

        while(current) {
            ++size;
            current = current->next;
        }

        if(size == 0)
            return head;

        k = k % size;

        if(k == 0) 
            return head;

        ListNode dummy;
        ListNode* ptr = &dummy;

        current = head;
        ListNode* last = nullptr;

        int count = size - k;
        while(count > 0) {
            ptr->next = new ListNode(current->val);
            ptr = ptr->next;
            last = ptr;
            current = current->next;
            --count;
        }

        ListNode dummy2;
        ptr = &dummy2;
        ListNode* last2 = nullptr;

        count = k;
        while(count > 0) {
            ptr->next = new ListNode(current->val);
            ptr = ptr->next;
            last2 = ptr;
            current = current->next;
            --count;
        }

        if(last2)
            last2->next = dummy.next;
        last->next = nullptr;

        auto result = dummy2.next;

        return result;
    }
};

int main(int argc, char** argv) {

    auto l = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    Solution s;
    auto r = s.rotateRight(l, 2);
    while(r) {
        std::cout << r->val << std::endl;
        r = r->next;
    }
}
