#include <functional>
#include <set>
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

class Solution {
public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> vs;

        std::set<int> level;

        std::function<void(TreeNode*, int)> f = [&](TreeNode* n, int l) {
            if(!n) return;

            auto [_, succ] = level.insert(l);

            if(succ)
                vs.push_back(n->val);
            f(n->right, l + 1);
            f(n->left, l + 1);

        };

        f(root, 0);

        return vs;
    }
};

int main(int argc, char** argv) { return 0; }
