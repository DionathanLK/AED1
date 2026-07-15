#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* invertTree(struct TreeNode* root);

int main() {
    struct TreeNode val1;
    val1.val = 1;
    val1.left = NULL;
    val1.right = NULL;

    struct TreeNode val2;
    val2.val = 3;
    val2.left = NULL;
    val2.right = NULL;

    struct TreeNode val3;
    val3.val = 6;
    val3.left = &val1;
    val3.right = &val2;

    struct TreeNode* root;
    root = &val3;

    root = invertTree(root);

    
    return 0;
}

struct TreeNode* invertTree(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    
    struct TreeNode* cp = root->left;
    root->left = root->right;
    root->right = cp;
    
    invertTree(root->left);
    invertTree(root->right);
    

    return root;
}