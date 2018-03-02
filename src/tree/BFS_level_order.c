/*
 *  Breadth First Search
 *
 *  (1) we implement queue
 *  (2) do BFS base on queue
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ListNode_s {
    struct TreeNode *data;
    struct ListNode_s *next;
};

struct Queue {
    struct ListNode_s* head; // dequeue
    struct ListNode_s* tail; // enqueue
    int    size;
};

static void
enqueue(struct Queue* q, struct TreeNode* node) {
    if (q->head == NULL) { // queue is empty
        struct ListNode_s* item = malloc(sizeof(struct ListNode_s));
        item->data = node;
        item->next = NULL;
        q->head = item;
        q->tail = item;
        q->size = 1;
    } else {
        struct ListNode_s* item = malloc(sizeof(struct ListNode_s));
        item->data = node;
        item->next = NULL;
        q->tail->next = item;
        q->tail = item;
        q->size++;
    }
};

static struct TreeNode*
dequeue(struct Queue* q) {
    if (q == NULL || q->head == NULL) {
        return NULL;
    } else if (q->head == q->tail) {
        struct TreeNode* t = q->head->data;
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return t;
    } else {
        struct TreeNode* t = q->head->data;
        free(q->head);
        q->head = q->head->next;
        q->size--;
        return t;
    }
};

static bool isEmpty(struct Queue *q)
{
    if (q->head == NULL) {
        return true;
    }
    return false;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    int    levelMaxSize = 100;
    int    **levelOrder = malloc(sizeof(int*) * levelMaxSize);
    int    levelOrderIndex = 0;
    struct Queue q = { 0 };
    int    level_size = 0;
    int*   level_array;
    
    if (root == NULL) return NULL;

    *columnSizes = malloc(sizeof(int) * levelMaxSize);
    // push root
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        // read the size of queue
        level_size = q.size; 
        printf("level size = %d\n", level_size);
        level_array = malloc(sizeof(int) * level_size);
        // dequeue all node from list(and push children to queue)
        for (int j = 0; j < level_size; j++) {
            struct TreeNode* node = dequeue(&q);
            level_array[j] = node->val;
            if (node->left != NULL) {
                enqueue(&q, node->left);
            }
            if (node->right != NULL) {
                enqueue(&q, node->right);
            }
        }
        /*if (levelOrderIndex >= levelMaxSize) {
            levelMaxSize *= 2;
            int **newOrder = malloc(sizeof(int*) * levelMaxSize);
            int 
        }*/
        (*columnSizes)[levelOrderIndex] = level_size;
        // push this level into levelOrder
        levelOrder[levelOrderIndex++] = level_array;
    }
    *returnSize = levelOrderIndex;
    return levelOrder;
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
    int level_num = 0;
    int *col_size;
    int **level_order = levelOrder(&root, &col_size, &level_num);
    for (int i = 0; i < level_num; i++) {
        printf("[");
        for (int j = 0; j < col_size[i]; j ++) {
            printf("%d, ", level_order[i][j]);    
        }
        printf("]\n");
    }
    return 0;
}
