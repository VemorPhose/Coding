<<<<<<< HEAD
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
Tree findMinNode(Tree tree) {
    if (tree == NULL)
        return NULL;
    Tree minLeft = findMinNode(tree->left);
    Tree minRight = findMinNode(tree->right);
    Tree min = tree;
    if (minLeft != NULL && minLeft->key < min->key)
        min = minLeft;
    if (minRight != NULL && minRight->key < min->key)
        min = minRight;
    return min;
}

// 11
Tree findMaxNode(Tree tree) {
    if (tree == NULL)
        return NULL;
    Tree maxLeft = findMaxNode(tree->left);
    Tree maxRight = findMaxNode(tree->right);
    Tree max = tree;
    if (maxLeft != NULL && maxLeft->key > max->key)
        max = maxLeft;
    if (maxRight != NULL && maxRight->key > max->key)
        max = maxRight;
    return max;
}

// 12
int isBST(Tree tree){
	if (!tree) return 1;
	if (tree -> left)
		if (tree -> key < findMaxNode(tree -> left)->key) return 0;
	if (tree -> right)
		if (tree -> key > findMinNode(tree -> right)->key) return 0;

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
    Tree tree = NULL, out = NULL;
    for(int i = 0; i < n; i++){
        tree = insertIntoBST(tree, keys[i], NULL);
    }
	printTree(tree);
    printf("\n");
	int f = 1, key = 0;
	while (f){
		printf("0. exit\n");		
		printf("1. insert into bst recursive\n");
		printf("2. insert into bst iterative\n");
		printf("3. min key in bst\n");
		printf("4. max key in bst\n");
		printf("5. find node by key in bst\n");
		printf("6. delete node by key in bst\n");
		printf("7. print inorder\n");
		printf("8. print preorder\n");
		printf("9. print postorder\n");
		printf("10. min key node in binary tree\n");
		printf("11. max key node in binary tree\n");
		printf("12. check if bst\n");
		printf("13. print tree\n\n");

		printf("enter choice: ");
		scanf("%d", &f);
		switch (f)
		{
		case 1:
			printf("enter key: ");
			scanf("%d", &key);
			insertIntoBST(tree, key, NULL);
			break;
		case 2:
			printf("enter key: ");
			scanf("%d", &key);
			insertIntoBSTIterative(tree, key);
			break;
		case 3:
			out = findMinTreeInBST(tree);
			printTree(out);
			break;
		case 4:
			out = findMaxTreeInBST(tree);
			printTree(out);
			break;
		case 5:
			printf("enter key: ");
			scanf("%d", &key);
			out = findTreeInBST(tree, key);
			printTree(out);
			break;
		case 6:
			printf("enter key: ");
			scanf("%d", &key);
			tree = deleteTreeFromBST(tree, key);
			break;
		case 7:
			printInOrder(tree);
			break;
		case 8:
			printPreOrder(tree);
			break;
		case 9:
			printPostOrder(tree);
			break;
		case 10:
			out = findMinNode(tree);
			printTree(tree);
		case 11:
			out = findMaxNode(tree);
			printTree(tree);
		case 12:
			key = isBST(tree);
			if (key) printf("yes\n");
			else printf("no\n");
			break;
		case 13:
			printTree(tree);
			break;
		
		default:
			break;
		}
	}
    return 0;
}
=======
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
Tree findMinNode(Tree tree) {
    if (tree == NULL)
        return NULL;
    Tree minLeft = findMinNode(tree->left);
    Tree minRight = findMinNode(tree->right);
    Tree min = tree;
    if (minLeft != NULL && minLeft->key < min->key)
        min = minLeft;
    if (minRight != NULL && minRight->key < min->key)
        min = minRight;
    return min;
}

// 11
Tree findMaxNode(Tree tree) {
    if (tree == NULL)
        return NULL;
    Tree maxLeft = findMaxNode(tree->left);
    Tree maxRight = findMaxNode(tree->right);
    Tree max = tree;
    if (maxLeft != NULL && maxLeft->key > max->key)
        max = maxLeft;
    if (maxRight != NULL && maxRight->key > max->key)
        max = maxRight;
    return max;
}

// 12
int isBST(Tree tree){
	if (!tree) return 1;
	if (tree -> left)
		if (tree -> key < findMaxNode(tree -> left)->key) return 0;
	if (tree -> right)
		if (tree -> key > findMinNode(tree -> right)->key) return 0;

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
    Tree tree = NULL, out = NULL;
    for(int i = 0; i < n; i++){
        tree = insertIntoBST(tree, keys[i], NULL);
    }
	printTree(tree);
    printf("\n");
	int f = 1, key = 0;
	while (f){
		printf("0. exit\n");		
		printf("1. insert into bst recursive\n");
		printf("2. insert into bst iterative\n");
		printf("3. min key in bst\n");
		printf("4. max key in bst\n");
		printf("5. find node by key in bst\n");
		printf("6. delete node by key in bst\n");
		printf("7. print inorder\n");
		printf("8. print preorder\n");
		printf("9. print postorder\n");
		printf("10. min key node in binary tree\n");
		printf("11. max key node in binary tree\n");
		printf("12. check if bst\n");
		printf("13. print tree\n\n");

		printf("enter choice: ");
		scanf("%d", &f);
		switch (f)
		{
		case 1:
			printf("enter key: ");
			scanf("%d", &key);
			insertIntoBST(tree, key, NULL);
			break;
		case 2:
			printf("enter key: ");
			scanf("%d", &key);
			insertIntoBSTIterative(tree, key);
			break;
		case 3:
			out = findMinTreeInBST(tree);
			printTree(out);
			break;
		case 4:
			out = findMaxTreeInBST(tree);
			printTree(out);
			break;
		case 5:
			printf("enter key: ");
			scanf("%d", &key);
			out = findTreeInBST(tree, key);
			printTree(out);
			break;
		case 6:
			printf("enter key: ");
			scanf("%d", &key);
			tree = deleteTreeFromBST(tree, key);
			break;
		case 7:
			printInOrder(tree);
			break;
		case 8:
			printPreOrder(tree);
			break;
		case 9:
			printPostOrder(tree);
			break;
		case 10:
			out = findMinNode(tree);
			printTree(tree);
		case 11:
			out = findMaxNode(tree);
			printTree(tree);
		case 12:
			key = isBST(tree);
			if (key) printf("yes\n");
			else printf("no\n");
			break;
		case 13:
			printTree(tree);
			break;
		
		default:
			break;
		}
	}
    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
