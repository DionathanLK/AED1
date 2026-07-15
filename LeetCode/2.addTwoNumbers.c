#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int sum = 0, carry = 0 , v1, v2;
    struct ListNode *head = NULL, *last = NULL;

    while (l1 != NULL || l2 != NULL || carry > 0) {

        v1 = l1 ? l1->val : 0;
        v2 = l2 ? l2->val : 0;

        sum = v1 + v2 + carry;
        carry = sum / 10;
        sum %= 10;

        struct ListNode* new = (struct ListNode*)malloc(sizeof(struct ListNode));
        new->val = sum;
        new->next = NULL;

        if (!head)
            head = new;
         else 
            last->next = new;
        
        last = new;

        l1 = (l1==NULL) ? NULL: l1->next;
        l2 = (l2==NULL) ? NULL: l2->next;
    }

    return head;
}

struct ListNode* createList(int* arr, int size) {
    if (size == 0) return NULL;

    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->val = arr[0];
    head->next = NULL;

    struct ListNode* current = head;
    for (int i = 1; i < size; i++) {
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        newNode->val = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }

    return head;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d", head->val);
        if (head->next) 
            printf(" -> ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    int arr1[] = {9};
    // int arr2[] = {1, 9};
    int arr2[] = {1, 9, 9, 9, 9, 9, 9, 9, 9, 9};

    struct ListNode* l1 = createList(arr1, 1);
    // struct ListNode* l2 = createList(arr2, 2);
    struct ListNode* l2 = createList(arr2, 10);

    struct ListNode* result = addTwoNumbers(l1, l2);

    printf("Resultado: ");
    printList(result);
    free(result);
    return 0;
}