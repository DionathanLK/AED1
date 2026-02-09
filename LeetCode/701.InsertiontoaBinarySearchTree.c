/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* insertIntoBST(struct TreeNode* root, int val) {
    
    if ( root == NULL) { //testar se a arvore e vazia
        struct TreeNode* newtree = malloc(sizeof(struct TreeNode));
        newtree -> val = val;
        newtree -> left = NULL;
        newtree -> right = NULL;
        return newtree;

    }
    
    struct TreeNode *head = root; //cabeça para percorrer

    if ( val < head->val ) {
        head -> left = insertIntoBST ( root -> left, val);

    }   else {
            head -> right =  insertIntoBST ( root -> right, val);
   
    }   
    
    return root;

}
