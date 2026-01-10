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
    std::vector<std::vector<int>> pathSum(TreeNode* p, int targetSum)
    {
        std::vector<std::vector<int>> vs;

        std::function<void(TreeNode*, std::vector<int>&, int)> f =
            [&](TreeNode* current, std::vector<int>& path, int currentSum) {
                if (!current)
                    return;

                auto sum = current->val + currentSum;

                path.push_back(current->val);
                if (sum == targetSum && !current->left && !current->right)
                {
                    vs.push_back(path);
                }

                f(current->left, path, sum);
                f(current->right, path, sum);

                path.pop_back();
            };

        std::vector<int> path;

        f(p, path, 0);

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
