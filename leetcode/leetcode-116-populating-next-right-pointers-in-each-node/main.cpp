#include <functional>
#include <queue>

class Node
{
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node()
        : val(0)
        , left(NULL)
        , right(NULL)
        , next(NULL)
    {}

    Node(int _val)
        : val(_val)
        , left(NULL)
        , right(NULL)
        , next(NULL)
    {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val)
        , left(_left)
        , right(_right)
        , next(_next)
    {}
};

class Solution
{
public:
    Node* connect(Node* root)
    {
        std::function<void(Node * root)> f = [](Node* n) {
            if (!n)
                return;

            std::queue<Node*> q;
            q.push(n);

            while (!q.empty())
            {
                auto prev = q.front();
                q.pop();

                auto size = q.size();

                if (prev->left)
                    q.push(prev->left);

                if (prev->right)
                    q.push(prev->right);

                for (auto i = 0; i < size; ++i)
                {
                    auto c = q.front();
                    q.pop();

                    if (c->left)
                        q.push(c->left);

                    if (c->right)
                        q.push(c->right);

                    prev->next = c;
                    prev = c;
                }
            }
        };

        f(root);

        return root;
    }
};

int main(int argc, char** argv) { return 0; }
