/*
 * The idea is merge sort
 * First, we need to divide link-list into two half
 * Then, we recursively sort them
 * Finally, we need to merge sorted list into one list
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/*struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (l1 == NULL) {
        return l2;
    } else if (l2 == NULL) {
        return l1;
    }

    if (l1->val <= l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}*/

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode l3;
    struct ListNode* t3 = &l3;
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            t3->next = l1;
            l1 = l1->next;
        } else {
            t3->next = l2;
            l2 = l2->next;
        }
        t3 = t3->next;
        t3->next = NULL;
    }
    t3->next = l1 ? l1 : l2;
    return l3.next;
}


struct ListNode* sortList(struct ListNode* head) {
    // use slow, fast pointer to divide link-list
    struct ListNode *prev, *slow = head, *fast = head;
    if (head == NULL || head->next == NULL) {
        return head;
    }
    while (slow != NULL && fast != NULL) {
        prev = slow;
        slow = slow->next;
        if (fast->next == NULL) {
            break;
        }
        fast = fast->next->next;
    }
    prev->next = NULL;

    head = sortList(head);
    slow = sortList(slow);
    return mergeTwoLists(head, slow);
}
