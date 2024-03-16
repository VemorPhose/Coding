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

int max(int a, int b){
	return a > b ? a : b;
}

int min(int a, int b){
	return a < b ? a : b;
}

// 1
Tree insertIntoBST(Tree tree, int key, Tree parent){
	if (!tree)
		return newTree(parent, key, NULL, NULL);
	if (key < tree -> key)
		tree -> left = insertIntoBST(tree -> left, key, tree);
	else
		tree -> right = insertIntoBST(tree -> right, key, tree);
	return tree;
}

// 2
Tree insertIntoBSTIterative(Tree tree, int key){
	if (!tree) return newTree(key, NULL, NULL, NULL);
	Tree current = tree;
	Tree parent = tree -> parent;
	while(current){
		parent = current;
		if (key < current -> key)
			current = current -> left;
		else
			current = current -> right;
	}
	if (key < parent -> key)
		parent -> left = newTree(key, NULL, parent, NULL);
	else
		parent -> right = newTree(key, NULL, parent, NULL);
	return tree;
}

// 3
Tree findMinTreeInBST(Tree tree){
	for (; tree -> left; tree = tree -> left) ;
	return tree;
}

// 4
Tree findMaxTreeInBST(Tree tree){
	for (; tree -> right; tree = tree -> right) ;
	return tree;
}

// 5
Tree findTreeInBST(Tree tree, int key){
	if (!tree)
		return NULL;
	if (key == tree -> key)
		return tree;
	if (key < tree -> key)
		return findTreeInBST(tree -> left, key);
	return findTreeInBST(tree -> right, key);
}

// 6
Tree deleteTreeFromBST(Tree tree, int key){
	if (!tree) {
        return NULL;
    }
	if (key < tree -> key){
		tree -> left = deleteTreeFromBST(tree -> left, key);
		return tree;
	}
	if (key > tree -> key){
		tree -> right = deleteTreeFromBST(tree -> right, key);
		return tree;
	}
    printf("Found %d\n", tree -> key);
	if (!tree -> left && !tree -> right){
		free(tree);
		return NULL;
	}
	if (tree -> left == NULL){
		Tree right = tree -> right;
		right -> parent = tree -> parent;
		free(tree);
		return right;
	}
    if (tree -> right == NULL){
        Tree left = tree -> left;
        left -> parent = tree -> parent;
        free(tree);
        return left;
	}
    Tree successor = findMinTreeInBST(tree -> right);
    tree -> key = successor -> key;
    tree -> right = deleteTreeFromBST(tree -> right, successor -> key);
    return tree ;
}

// 7
void printInOrder(Tree tree){
    if(!tree)
        return;
    printInOrder(tree->left);
    printf("%d ", tree->key);
    printInOrder(tree->right);
}

// 8
void printPreOrder(Tree tree){
    if(!tree)
        return;
    printf("%d ", tree->key);
    printPreOrder(tree->left);
    printPreOrder(tree->right);
}

// 9
void printPostOrder(Tree tree){
    if(!tree)
        return;
    printPostOrder(tree->left);
    printPostOrder(tree->right);
    printf("%d ", tree->key);
}

// 10
int minKey(Tree tree){
	if (!tree) return 0;
	if (tree -> left == NULL && tree -> right == NULL)
		return tree -> key;
	if (!tree -> left)
		return min(tree -> key, minKey(tree -> right));
	if (!tree -> right)
		return min(tree -> key, minKey(tree -> left));
	int minLeftRight = min(minKey(tree -> left), minKey(tree -> right));
	return min(tree -> key, minLeftRight);
	//OR return min(tree -> key, min(minKey(tree -> left), minKey(tree -> right)));
}

// 11
int maxKey(Tree tree){
	if (!tree) return 0;
	if (tree -> left == NULL && tree -> right == NULL)
		return tree -> key;
	if (!tree -> left)
		return max(tree -> key, maxKey(tree -> right));
	if (!tree -> right)
		return max(tree -> key, maxKey(tree -> left));
	int maxLeftRight = max(maxKey(tree -> left), maxKey(tree -> right));
	return max(tree -> key, maxLeftRight);
	//OR return max(tree -> key, max(maxKey(tree -> left), maxKey(tree -> right)));
}

// 12
int isBST(Tree tree){
	if (!tree) return 1;
	if (tree -> left)
		if (tree -> key < maxKey(tree -> left)) return 0;
	if (tree -> right)
		if (tree -> key > minKey(tree -> right)) return 0;

	int x = isBST(tree -> left);
	int y = isBST(tree -> right);
	printf("At %d, got: %d & %d\n", tree -> key, x, y);
	return x && y;
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

int main (){
    int keys[] = {144, 150, 148, 99, 163, 119, 167, 141, 136, 155};
    int n = sizeof(keys)/sizeof(keys[0]);
    Tree bst = NULL;
    for(int i = 0; i < n; i++){
        bst = insertIntoBST(bst, keys[i], NULL);
        printTree(bst);
        printf("\n");
    }
    return 0;
}
