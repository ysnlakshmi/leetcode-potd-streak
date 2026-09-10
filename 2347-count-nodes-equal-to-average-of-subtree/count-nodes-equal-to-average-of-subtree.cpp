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
private:
    int matchingNodesCount = 0;

    pair<int, int> dfs(TreeNode* node) {
        if (!node) {
            return {0, 0};
        }

        auto [leftSum, leftCount] = dfs(node->left);
        auto [rightSum, rightCount] = dfs(node->right);

        int totalSum = node->val + leftSum + rightSum;
        int totalCount = 1 + leftCount + rightCount;

        if (node->val == totalSum / totalCount) {
            matchingNodesCount++;
        }

        return {totalSum, totalCount};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        matchingNodesCount = 0;
        dfs(root);
        return matchingNodesCount;
    }
};