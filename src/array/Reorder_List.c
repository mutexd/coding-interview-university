/*
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};


void
recur_reorder(struct ListNode** head, struct ListNode* cur) {
    if (cur == NULL) {
       return;
    }
    recur_reorder(head, cur->next);
    if ((*head) == NULL) {
        printf("head is null\n");
        return;
    } else if ((*head) == cur) {
        printf("it's odd list, %d\n", cur->val);
        cur->next = NULL;
        (*head) = NULL;
        return;
    } else if ((*head)->next == cur) {
        printf("it's even list, %d\n", cur->val);
        cur->next = NULL;
        (*head) = NULL;
        return;
    }
    
    // insert cur after head
    struct ListNode* tmp = (*head)->next;
    (*head)->next = cur;
    cur->next = tmp;
    
    // move head
    (*head) = tmp;
    printf("moved head = %d\n", (*head)->val);
}

void reorderList(struct ListNode* head) {
    if (head == NULL) return;
    recur_reorder(&head, head->next);
}

int main(int argc, char** argv) 
{
    struct ListNode head = { 0, NULL };
    struct ListNode* prev = &head;
    for (int i = 1; i < 5; i ++) {
        struct ListNode* n = malloc(sizeof(struct ListNode));
        n->val = i;
        n->next = NULL;
        prev->next = n;
        prev = n;
    }
    reorderList(&head);
    prev = &head;
    while (prev != NULL) {
        printf("%d,", prev->val);
        prev = prev->next;
    }
    printf("\n");
    return 0;
}
