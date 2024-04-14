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
		return newTree(parent, key, NULL, NULL);
	if (key < tree -> key)
		tree -> left = insertIntoBST(tree -> left, key, tree);
	else
		tree -> right = insertIntoBST(tree -> right, key, tree);
	return tree;
}

Tree insertIntoBSTIterative(Tree tree, int key){
	if (!tree) return newTree(NULL, key, NULL, NULL);
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
		parent -> left = newTree(parent, key, NULL, NULL);
	else
		parent -> right = newTree(parent, key, NULL, NULL);
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

int max(int a, int b){
	return a > b ? a : b;
}

int height(Tree tree){
	if (!tree) return -1;
	int heightLeft = height(tree -> left);
	int heightRight = height(tree -> right);
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

int isBST(Tree tree){
	if (!tree) return 1;
	if (tree -> left)	
		if (tree -> key < maxKey(tree -> left)) return 0;
	if (tree -> right)
		if (tree -> key > minKey(tree -> right)) return 0;

	int x = isBST(tree -> left);
	int y = isBST(tree -> right);
	return x && y;
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
	Tree t = newTree(tree, tree -> key, left, NULL);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

Tree mirror(Tree tree){
	if (!tree) return NULL;
	Tree right = mirror(tree -> left);
	Tree left = mirror(tree -> right);
	Tree t = newTree(tree, tree -> key, left, NULL);
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

int countNodes(Tree tree){	
	return tree? 1 + countNodes(tree->left) + countNodes(tree->right) : 0;
}

int countLeafNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 1;
	return countLeafNodes(tree->left) + countLeafNodes(tree->right);
}

int countInternalNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 0;
	return 1+ countInternalNodes(tree->left) + countInternalNodes(tree->right);
}

int linearSearch(int a[], int start, int end, int key){
	for(;start<=end;start++)
		if(a[start] == key)
			return start;
	return -1;
}

Tree buildTreeHelperInPost(int post[], int in[], int inStart, int inEnd, int *postIndex){
	if (inStart>inEnd) return NULL;
	Tree tree =  newTree(NULL, post[*postIndex], NULL, NULL);
	(*postIndex)--;
	int index = linearSearch(in, inStart, inEnd, tree->key);
	// right called before left coz postIndex being decremented that way
	tree->right = buildTreeHelperInPost(post, in, index+1, inEnd, postIndex);
	tree->left = buildTreeHelperInPost(post, in, inStart, index-1, postIndex);
	return tree;
}

Tree buildTreeInPost(int post[], int in[], int n){
	int inStart = 0;
	int inEnd = n-1;
	int postIndex = n-1;
	// postIndex passed by reference to not lose decrement progress through recursion
	return buildTreeHelperInPost(post, in, inStart, inEnd, &postIndex);
}

Tree buildTreeHelperInPre(int pre[], int in[], int inStart, int inEnd, int *preIndex){
	if (inStart>inEnd) return NULL;
	Tree tree =  newTree(NULL, pre[*preIndex], NULL, NULL);
	(*preIndex)++;
	int index = linearSearch(in, inStart, inEnd, tree->key);
	// left called before right coz preIndex being incremented that way
	tree->left = buildTreeHelperInPre(pre, in, inStart, index-1, preIndex);
	tree->right = buildTreeHelperInPre(pre, in, index+1, inEnd, preIndex);
	return tree;
}

Tree buildTreeInPre(int pre[], int in[], int n){
	int inStart = 0;
	int inEnd = n-1;
	int preIndex = 0;
	// preIndex passed by reference to not lose increment progress through recursion
	return buildTreeHelperInPre(pre, in, inStart, inEnd, &preIndex);
}

int main() {
    int keys[] = {144, 150, 148, 99, 163, 119, 167, 141, 136, 155};
    int n = sizeof(keys)/sizeof(keys[0]);
    Tree bst = NULL;
    for(int i = 0; i < n; i++){
        bst = insertIntoBST(bst, keys[i], NULL);
    }
    printTree(bst);
    printf("\n");

	Tree newBst = NULL;
	int pre[] = {144, 99, 119, 141, 136, 150, 148, 163, 155, 167};
	int in[] = {99, 119, 136, 141, 144, 148, 150, 155, 163, 167};
	int post[] = {136, 141, 119, 99, 148, 155, 167, 163, 150, 144};

	newBst = buildTreeInPost(post, in, n);
	printf("rebuilding from post & in: \n");
	printTree(newBst);
    printf("\n");

	newBst = buildTreeInPre(pre, in, n);
	printf("rebuilding from pre & in: \n");
	printTree(newBst);
    printf("\n");

    return 0;
}
