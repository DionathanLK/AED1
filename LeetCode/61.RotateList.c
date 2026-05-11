/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {

    
    int tamlist = 1; //testar tam lista
    struct ListNode* ult = head; //pra copiar a lista e achar ultimo

    if ( head == NULL || head -> next == NULL ) {
        //testar se algum dos valores e nulo
        return head;
    }

    while ( ult -> next != NULL ) { 
        //contar o tam da lista sem mudar a lista
        ult = ult -> next; //achar ultimo
        tamlist++;

    }

    k = k % tamlist; 
    //otimizar o numero de vezes que precisa rotacionar pois está ultrapassando temp limite
    if ( k == 0 ) {

        return head;

    }

    ult -> next = head; //ultimo prox recebe o primeiro

    for ( int i = 0; i < tamlist - k - 1; i++ ) {
        //quantas vezes rotacionar a direita

      head = head -> next; 

    }
    
    struct ListNode* newhead = head->next;

    // Quebra o ciclo
    head->next = NULL;

    return newhead;
}