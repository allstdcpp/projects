#include <cctype>
#include <functional>
#include <string>
#include <vector>

class MyLinkedList
{
public:

    struct Node
    {
        int value{};
        Node* next{};
    };

    MyLinkedList() = default;

    int get(int index)
    {
        if (index >= size_)
            return -1;

        auto current = head_;
        while (current)
        {
            if (index-- == 0)
                return current->value;
            current = current->next;
        }
        return -1;
    }

    void addAtHead(int val)
    {
        head_ = new Node{val, head_};
        ++size_;
    }

    void addAtTail(int val)
    {
        auto current = head_;

        while (current && current->next)
        {
            current = current->next;
        }
        if (!current)
        {
            addAtHead(val);
        }
        else
        {
            current->next = new Node{val, nullptr};
            ++size_;
        }
    }

    void addAtIndex(int index, int val)
    {
        if (index <= size_)
        {
            auto current = head_;
            Node* prev = nullptr;
            while (current)
            {
                if (index-- == 0)
                    break;
                prev = current;
                current = current->next;
            }

            if (!prev)
                addAtHead(val);
            else
            {
                prev->next = new Node{val, current};
                ++size_;
            }
        }
    }

    void deleteAtIndex(int index)
    {
        if (index < size_)
        {
            auto current = head_;
            Node* prev = nullptr;
            while (current)
            {
                if (index-- == 0)
                    break;
                prev = current;
                current = current->next;
            }

            if (!prev)
            {
                if (head_)
                {
                    auto next = head_->next;
                    delete head_;
                    head_ = next;
                }
            }
            else if (current)
            {
                auto next = current->next;
                delete current;
                prev->next = next;
            }

            --size_;
        }
    }
private:
    Node* head_{};
    size_t size_{};
};

int main(int argc, char** argv) { return 0; }
