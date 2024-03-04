#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

typedef struct tree_t *Tree;
typedef int Type;

struct tree_t{
    Tree parent;
    Type key;   
    Tree left, right; 
};

Tree newTree(Tree parent, Type key, Tree left, Tree right){
    Tree tree = (Tree) calloc(1, sizeof(struct tree_t));
    assert(tree);
    tree->parent = parent;
    tree->key = key;
    tree->left = left;
    tree->right = right;
    return tree;
}

void printPreOrder(Tree tree){
    if(!tree)
        return;
    printf("%d ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}

void printInOrder(Tree tree){
    if(!tree)
        return;
    printInOrder(tree->left);
    printf("%d ", tree->key);
    printInOrder(tree->right);
}

void printPostOrder(Tree tree){
    if(!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%d ", tree->key);
}

void printTree(Tree tree){
    printf("PreOrder: ");
    printPreOrder(tree);
    printf("\n");
    printf("InOrder: ");
    printInOrder(tree);
    printf("\n");
    printf("PostOrder: ");
    printPostOrder(tree);
    printf("\n");
}

Tree insertIntoBST(Tree tree, Type key){
    if (!tree)
        return newTree(tree, key, NULL, NULL); // base case when no node, new node created and its address returned to parent node to assign
    if (key < tree->key)
        tree->left = insertIntoBST(tree->left, key); // after recursive call, immediate child gets assigned to tree->left
    else
        tree->right = insertIntoBST(tree->right, key); // same logic after recursive call
    return tree; // returning to assign to parent node
}

int main() {
    int keys[] = {144, 150, 148, 99, 163, 119, 167, 141, 136, 155};
    int n = sizeof(keys)/sizeof(keys[0]);
    Tree bst = NULL;
    for(int i = 0; i < n; i++){
        bst = insertIntoBST(bst, keys[i]);
        printTree(bst);
        printf("\n");
    }

    return 0;
}