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

void printInOrder(Tree tree){
    if(!tree)
        return;
    printInOrder(tree->left);
    printf("%d ", tree->key);
    printInOrder(tree->right);
}

void printPreOrder(Tree tree){
    if(!tree)
        return;
    printf("%d ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}

void printPostOrder(Tree tree){
    if(!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%d ", tree->key);
}
