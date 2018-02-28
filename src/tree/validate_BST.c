/*
 * We'll try to validate the BST property here
 *
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};


bool validateBST(struct TreeNode* root, int* min, int* max) {
    int left_min, left_max;
    int right_min, right_max;
    bool left_v, right_v;

    if (root->left == NULL) {
        left_min = root->val;
    } else {
        left_v = validateBST(root->left, &left_min, &left_max);
        if (left_v == false || left_max >= root->val) {
            return false;
        }
    }

    if (root->right == NULL) {
        right_max = root->val;
    } else {
        right_v = validateBST(root->right, &right_min, &right_max);
        if (right_v == false || right_min <= root->val) {
            return false;
        }
    }

    // fill min/max
    *max = right_max;
    *min = left_min;
    return true;
}

bool isValidBST(struct TreeNode* root) {
    int min, max;
    if (root == NULL) {
        return true;
    }
    return validateBST(root, &min, &max);
}
