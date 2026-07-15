/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    
    struct ListNode* current = head;
    struct ListNode* prox;
    int num     = 0;
    int atual = current->val;
    

    while ( current != NULL ) {

        num++;
        current    = current->next;
        
    }

    *returnSize = num;
    int* node = ( int* ) malloc ( num * sizeof ( int ) );
    int  i    = 0;
    current = head;

    while ( current != NULL ) {
        prox    = current->next;
        atual   = current->val;

        while ( prox != NULL ) {

            if ( atual < prox->val ) {
                
                atual = prox->val;
                break;

            }
            prox = prox->next;

        }
        if ( atual == current->val ) {
            atual = 0;

        }

        node[i] = atual;
        i++; 
        current = current->next;

    }
    
    return node;
}