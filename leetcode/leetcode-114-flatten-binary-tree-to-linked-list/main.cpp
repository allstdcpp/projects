#include <functional>
#include <unordered_map>
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
    void flatten(TreeNode* root)
    {
        while (root)
        {
            if (root->left)
            {
                auto temp = root->right; // save current right

                root->right = root->left; // set right to the left

                auto current = root->left;
                root->left = nullptr; // clear

                while (current->right)
                    current = current->right;
                current->right = temp; // update
            }
            root = root->right;
        }
    }
};

int main(int argc, char** argv) {}
