#include <stack>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {}
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right)
    {}
};

class BSTIterator
{
public:
    BSTIterator(TreeNode* root)
    {
        auto current = root;
        while (current)
        {
            s_.push(current);
            current = current->left;
        }
    }

    int next()
    {
        auto result = s_.top();
        s_.pop();

        auto current = result->right;
        while (current)
        {
            s_.push(current);
            current = current->left;
        }
        return result->val;
    }

    bool hasNext() { return !s_.empty(); }
private:
    std::stack<TreeNode*> s_;
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main(int argc, char** argv) { return 0; }
