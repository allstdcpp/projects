#include <functional>
#include <iostream>
#include <vector>

/**
 * Definition for a binary tree node.
 */
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
    int maxDepth(TreeNode* root)
    {
        if (!root)
            return 0;

        auto l = maxDepth(root->left);
        auto r = maxDepth(root->right);

        return std::max(l, r) + 1;
    }
};
int main(int argc, char** argv) { return 0; }
