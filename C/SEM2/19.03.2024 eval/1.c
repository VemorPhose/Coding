#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
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

Tree clone(Tree tree){
	if (!tree) return NULL;
	Tree left = clone(tree -> left);
	Tree right = clone(tree -> right);
	Tree t = newTree(tree->parent, tree->key, left, right);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

Tree insertIntoBST(Tree tree, int key, Tree parent){
	if (!tree)
		return newTree(parent, key, NULL, NULL);
	if (key < tree -> key)
		tree -> left = insertIntoBST(tree -> left, key, tree);
	else
		tree -> right = insertIntoBST(tree -> right, key, tree);
	return tree;
}

int subTreeSumTree(Tree tree) {
    if (!tree)
        return 0;
    int sTreeSumLeft = subTreeSumTree(tree->left);
    int sTreeSumRight = subTreeSumTree(tree->right);
    tree->key += sTreeSumLeft + sTreeSumRight;
    return tree->key;
}

Tree findTreeInBST(Tree tree, int key, Tree sTreeSum){
	if (!tree)
		return NULL;
	if (key == tree -> key)
		return sTreeSum;
	if (key < tree -> key)
		return findTreeInBST(tree -> left, key, sTreeSum->left);
	return findTreeInBST(tree -> right, key, sTreeSum->right);
}

int main() {
    Tree tree = NULL;
    int n = 0, key = 0;
    printf("enter number of nodes: ");
    scanf("%d", &n);
    printf("enter node keys: ");
    for (int i = 0; i < n; i++){
        scanf("%d", &key);
        tree = insertIntoBST(tree, key, NULL);
    }
    printTree(tree);
    Tree sTreeSum = clone(tree);
    subTreeSumTree(sTreeSum);
    printTree(sTreeSum);

    Tree out = NULL;
    printf("enter number of queries: ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        printf("enter key to find: ");
        scanf("%d", &key);
        out = findTreeInBST(tree, key, sTreeSum);
        if (!out)
            printf("key not found!\n");
        else printf("subTreeSum at node is %d\n", out->key);
    }

    return 0;
}
