/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool traverse(struct TreeNode* left, struct TreeNode* right)
{
    if (left == NULL || right == NULL) {
        if (left == right) {
            return true;
        } else 
            return false;
    }
    if (traverse(left->left, right->right) == false) {
        return false;
    }
    if (traverse(left->right, right->left) == false) {
        return false;
    }
    if (left->val == right->val) {
        return true;
    }
    return false;
}

bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return traverse(root->left, root->right);
}
