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

Tree insertIntoBST(Tree tree, int key, Tree parent){
	if (!tree) 
		return newTree(key, NULL, parent, NULL);
	if (key < tree -> key)
		tree -> left = insertIntoBST(tree -> left, key, tree);
	else
		tree -> right = insertIntoBST(tree -> right, key, tree);
	return tree;
}

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

Tree findTreeInBST(Tree tree, int key){
	if (!tree)
		return NULL;
	if (key == tree -> key)
		return tree;
	if (key < tree -> key)	
		return findTreeInBST(tree -> left, key);
	return findTreeInBST(tree -> right, key);
}

Tree findTreeInBSTIterative(Tree tree, int key){
	while (tree){
		if (key == tree -> key)
			return tree;
		if (key < tree -> key)	
			tree = tree -> left;
		else	
			tree = tree -> right;
	}
	return NULL;
}

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

int max(int a, int b){
	return a > b ? a : b;
}

int height(Tree tree){
	if (!tree) return 0;
	int heightLeft = height(tree -> left);
	int heightRight = height(tree -> right);
	printf("At %3d, Left: %3d, Right: %3d\n", tree -> key, heightLeft, heightRight);
	return max(heightLeft, heightRight) + 1;
}

int depth(Tree tree){
	int depth = 0;
	for (; tree -> parent; tree = tree -> parent)
		depth++;
	return depth;
}

Tree findMinTreeInBST(Tree tree){
	for (; tree -> left; tree = tree -> left) ;
	return tree;
}

Tree findMaxTreeInBST(Tree tree){
	for (; tree -> right; tree = tree -> right) ;
	return tree;
}

int min(int a, int b){
	return a < b? a : b;
}

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

/*
	Delete tree:
		1. NULL - do nothing
		2. Single node (no child / leaf node) - Delete and return NULL
		3. One child - Child replaces parent
		4. Two children - Choose inorder predecessor/ successor
*/

Tree deleteTreeFromBST(Tree tree, int key){
	if (!tree) {
        printf("KEY NOT FOUND\n");
        return NULL;
    }
	if (key < tree -> key){
        printf("At %d, going left to delete %d\n", tree -> key, key);
		tree -> left = deleteTreeFromBST(tree -> left, key);
		return tree;
	}
	if (key > tree -> key){
        printf("At %d, going right to delete %d\n", tree -> key, key);
		tree -> right = deleteTreeFromBST(tree -> right, key);
		return tree;
	}
    // key == tree -> key
    printf("Found %d\n", tree -> key);
	if (!tree -> left && !tree -> right){
        printf("At %d with no children, going to delete %d\n", tree -> key, key);
		free(tree);
		return NULL;
	}
	if (tree -> left == NULL){
        printf("At %d with only right child, going to delete %d\n", tree -> key, key);
		Tree right = tree -> right;
		right -> parent = tree -> parent;
		free(tree);
		return right;
	}
    if (tree -> right == NULL){
        printf("At %d with only left child, going to delete %d\n", tree -> key, key);
        Tree left = tree -> left;
        left -> parent = tree -> parent;
        free(tree);
        return left;
	}
    Tree successor = findMinTreeInBST(tree -> right);
    printf("At %d with both children, going to delete %d & successor is %d\n", tree -> key, key, successor -> key);
    tree -> key = successor -> key;
    tree -> right = deleteTreeFromBST(tree -> right, successor -> key);
    return tree ;
}

Tree findSuccessor(Tree tree){
	if (!tree ) return NULL;
	if (tree -> right)
		return findMinTreeInBST(tree -> right);
	Tree successor = tree -> parent;
	// while (successor && tree == successor -> right){
	while (successor && tree -> key > successor -> key){
		tree = successor;
		successor = successor -> parent;
	}
	return successor;
}

Tree findPredecessor(Tree tree){
	if (!tree ) return NULL;
	if (tree -> left)
		return findMaxTreeInBST(tree -> left);
	Tree predecessor = tree -> parent;
	// while (predecessor && tree == predecessor -> left){
	while (predecessor && tree -> key < predecessor -> key){
		tree = predecessor;
		predecessor = predecessor -> parent;
	}
	return predecessor;
}

int isIdentical(Tree t1, Tree t2){
	if (!t1 && !t2) return 1;
	if ((!t1 && t2) || (t1 && !t2)) return 0;
	if (t1 -> key != t2 -> key) return 0;
	return isIdentical(t1 -> left, t2 -> left) && isIdentical(t1 -> right, t2 -> right);
}

int isIdenticalAlternate(Tree t1, Tree t2){
	if (t1 == t2) return 1;
	if (
		(t1 == NULL && t2 != NULL)
		||
		(t1 != NULL && t2 == NULL)
	) return 0;
	return
		(t1->key == t2->key)
		&&
		isIdenticalAlternate(t1->left, t2->left)
		&&
		isIdenticalAlternate(t1->right, t2->right);
}

Tree clone(Tree tree){
	if (!tree) return NULL;
	Tree left = clone(tree -> left);
	Tree right = clone(tree -> right);
	Tree t = newTree(tree -> key, left, tree, NULL);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

Tree mirror(Tree tree){
	if (!tree) return NULL;
	Tree right = mirror(tree -> left);
	Tree left = mirror(tree -> right);
	Tree t = newTree(tree -> key, left, tree, NULL);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

Tree findTree(Tree tree, int key) {
	if (!tree) return NULL;
	if (key == tree->key) return tree;
	Tree foundLeft = findTree(tree->left, key);
	if (foundLeft)
		return foundLeft;
	return findTree(tree->right, key);
}

int main() {
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
