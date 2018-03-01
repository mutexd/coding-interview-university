/*
 * We implement the detele function of BST
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/*
 * First, we need to search the node
 *
 * When the target node is leaf, directly delete it.
 * When the target node has one child, do link-list style deletion
 * When the target node has two child --> we need to rotate
 *      after rotation, we should be able to delete easily
 *
 *
 *
 */
static int _childNum(struct TreeNode* root) {
    int num = 0;
    if (root->left != NULL) num++;
    if (root->right != NULL) num++;
    return num;
}
struct TreeNode* _delete(struct TreeNode* root, int key, struct TreeNode** dir)
{
    if (root == NULL) return NULL;
    if (key < root->val) { // need to go left
        _delete(root->left, key, &root->left);
        return root;
    } else if (key > root->val) {
        _delete(root->right, key, &root->right);
        return root;
    } else { // target node
        if (root->left == NULL && root->right == NULL) {
            // leaf, directly delete
            (*dir) = NULL;
            free(root);
            root = NULL;
        } else if (root->left != NULL && root->right != NULL) {
            // need rotation
            struct TreeNode* p = root->right->left;
            root->right->left = root;
            (*dir) = root->right;
            root->right = p;
            // then delete
            _delete(root, key, &(*dir)->left);
            return (*dir);
        } else if (root->left != NULL) {
            (*dir) = root->left; 
            free(root);
            root = NULL;
        } else {
            (*dir) = root->right;
            free(root);;
            root  = NULL;
        }
    }
    return (*dir);
}

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    struct TreeNode fakeRoot;
    return _delete(root, key, &fakeRoot.left);
}

int main(int argc, char **argv)
{
    struct TreeNode root, left, right;
    root.val = 3;
    root.left = &left;
    root.right = &right;
    left.left = NULL;
    left.right = NULL;
    right.left = NULL;
    right.right = NULL;
    left.val = 1;
    right.val = 5;
    struct TreeNode* ret = deleteNode(&root, 1);
    printf("left = %p\n", ret->left);
}
