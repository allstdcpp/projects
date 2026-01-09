#include <functional>
#include <iostream>
#include <vector>

/**
 * Definition for a binary tree node.
 */
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
class Solution
{
public:
    bool hasPathSum(TreeNode* p, int targetSum)
    {
        std::function<bool(TreeNode*, int)> f = [&](TreeNode* current, int currentSum) {
            if(!current) return false;

            auto sum = current->val + currentSum;

            if(sum == targetSum && !current->left && !current->right) return true;

            auto hasLeftSum = f(current->left, sum);
            auto hasRightSum = f(current->right, sum);

            return hasLeftSum || hasRightSum;
        };

        return f(p, 0);
    }
};

int main(int argc, char** argv)
{
    return 0;
}
