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

struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL) return NULL;
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left != NULL && root->right != NULL) {
            struct TreeNode* p = root->right;
            root->right = p->left;
            p->left = deleteNode(root, key);
            return p;
        } else if (root->left != NULL) {
            return root->left;
        } else { // both root->right != || == NULL satisfy
            return root->right;
        }
    }
    return root;
}

#if 0 // not a good solution
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
#endif
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
