#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

//  Definition for a binary tree node.
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
class Solution
{
public:

    bool exists(TreeNode* p, TreeNode* q)
    {
        if ((p->left == nullptr) ^ (q->left == nullptr))
            return false;
        if ((p->right == nullptr) ^ (q->right == nullptr))
            return false;
        if (p->val != q->val)
            return false;
        auto left = ((!p->left && !q->left) || exists(p->left, q->left));
        auto right = ((!p->right && !q->right) || exists(p->right, q->right));

        return left && right;
    }

    bool isSubtree(TreeNode* p, TreeNode* q)
    {
        if (!p || !q)
            return false;

        if (exists(p, q))
            return true;

        return isSubtree(p->left, q) || isSubtree(p->right, q);
    }
};

int main(int argc, char** argv) {}
