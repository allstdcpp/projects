#include <algorithm>
#include <queue>
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
    std::vector<std::vector<int>> levelOrderBottom(TreeNode* root)
    {
        std::vector<std::vector<int>> result;

        if (root)
        {
            std::queue<TreeNode*> q;
            q.push(root);

            while (!q.empty())
            {
                auto size = q.size();
                std::vector<int> vs;

                for (int i = 0; i < q.size(); ++i)
                {
                    vs.push_back(q.front()->val);

                    auto t = q.front();
                    q.pop();

                    if (t->left)
                    {
                        q.push(t->left);
                    }
                    if (t->right)
                    {
                        q.push(t->right);
                    }
                }
                result.push_back(vs);
            }
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};

int main(int argc, char** argv) { return 0; }
