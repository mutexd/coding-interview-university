/*
 * Here we try to check whether the BST is balanced or not.
 *
 * Definiton of balanced: a binary tree in which the depth of the 
 *          two subtrees of every node never differ by more than 1
 *
 * (1) We first implement the height() recursive function and calculate the height of each node
 * (2) then, we traverse the tree to check the balanced property
 * Complexity: O(n + n) 
 *
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

static int max(int a, int b)
{
    if (a <= b) {
        return b;
    } else {
        return a;
    }
}

#if 0
static int height(struct TreeNode* root) {
    if (root == NULL) {
        return -1;
    }
    return max(height(root->left), height(root->right)) + 1;
}

bool isBalanced(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    if (isBalanced(root->left) == false || isBalanced(root->right) == false) {
        return false;
    }
    int h_left = height(root->left);
    int h_right = height(root->right);
    if (abs(h_left - h_right) <= 1) {
        return true;
    }
    return false;
}
#endif
// -1: non-balanced
// >0: height
static int height(struct TreeNode* root) {
    if (root == NULL) return 0;

    int left_h = height(root->left);
    int right_h = height(root->right);
    if (left_h == -1 || right_h == -1) {
        return -1;
    }
    if (abs(left_h - right_h) <= 1) {
        return max(left_h, right_h) + 1;
    }
    return -1;
}

bool isBalanced(struct TreeNode* root) {
    if (height(root) == -1) {
        return false;
    }
    return true;
}

