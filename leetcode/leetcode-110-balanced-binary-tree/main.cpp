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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        
        bool balanced = true;

        std::function<int(TreeNode*)> f = [&](TreeNode* n) {

            if(!balanced)
                return 0;

            if(!n) return 0;

            auto l = f(n->left);
            auto r = f(n->right);

            auto d = std::abs(l - r);

            if(d > 1)
                balanced = false;

            return std::max(l, r)  + 1;
        };

        f(root);

        return balanced;
    }
};
int main(int argc, char** argv)
{
    return 0;
}
