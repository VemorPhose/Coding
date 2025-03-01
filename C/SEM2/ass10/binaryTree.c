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

Tree insertIntoBST(Tree tree, int key, Tree parent){
	if (!tree)
		return newTree(parent, key, NULL, NULL);
	if (key < tree -> key)
		tree -> left = insertIntoBST(tree -> left, key, tree);
	else
		tree -> right = insertIntoBST(tree -> right, key, tree);
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

// 1
Tree findNode(Tree tree, Type key) {
    if (tree == NULL)
        return NULL;
    if (tree->key == key) return tree;
    Tree foundLeft = NULL, foundRight = NULL;
    if (tree->left)
        foundLeft = findNode(tree->left, key);
    if (tree->right)
        foundRight = findNode(tree->right, key);
    if (foundLeft != NULL)
        return foundLeft;
    return foundRight;
}

// 2
int height(Tree tree){
	if (!tree) return 0;
	int heightLeft = height(tree -> left);
	int heightRight = height(tree -> right);
	printf("At %3d, Left: %3d, Right: %3d\n", tree -> key, heightLeft, heightRight);
	return max(heightLeft, heightRight) + 1;
}

// 3
int depth(Tree tree){
	int depth = 0;
	for (; tree -> parent; tree = tree -> parent)
		depth++;
	return depth;
}

// 4
Tree mirror(Tree tree){
	if (!tree) return NULL;
	Tree right = mirror(tree -> left);
	Tree left = mirror(tree -> right);
	Tree t = newTree(tree->parent, tree->key, left, right);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

// 5
Tree clone(Tree tree){
	if (!tree) return NULL;
	Tree left = clone(tree -> left);
	Tree right = clone(tree -> right);
	Tree t = newTree(tree->parent, tree->key, left, right);
	if (left) left -> parent = t;
	if (right) right -> parent = t;
	return t;
}

// 6
int isIdentical(Tree t1, Tree t2){
	if (!t1 && !t2) return 1;
	if ((!t1 && t2) || (t1 && !t2)) return 0;
	if (t1 -> key != t2 -> key) return 0;
	return isIdentical(t1 -> left, t2 -> left) && isIdentical(t1 -> right, t2 -> right);
}

// 7
Tree deleteBinaryTree(Tree tree){
    if (!tree) return NULL;
    if (tree->left)
        tree->left = deleteBinaryTree(tree->left);
    if (tree->right)
        tree->right = deleteBinaryTree(tree->right);
    tree->parent = NULL;
    free(tree);
    return NULL;
}

Tree findMinTreeInBST(Tree tree){
	for (; tree -> left; tree = tree -> left) ;
	return tree;
}

Tree findMaxTreeInBST(Tree tree){
	for (; tree -> right; tree = tree -> right) ;
	return tree;
}

// 8
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

// 9
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

<<<<<<< HEAD
// 10
int countLeafNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 1;
	return countLeafNodes(tree->left) + countLeafNodes(tree->right);
}

// 11
int countNonLeafNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 0;
	return 1+ countNonLeafNodes(tree->left) + countNonLeafNodes(tree->right);
}
=======
// 10
int countLeafNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 1;
	return countLeafNodes(tree->left) + countLeafNodes(tree->right);
}

// 11
int countNonLeafNodes(Tree tree){
	if(!tree) return 0;
	if(tree->left == NULL && tree->right == NULL)
		return 0;
	return 1+ countNonLeafNodes(tree->left) + countNonLeafNodes(tree->right);
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2

// 12
void printLeafInOrder(Tree tree){
    if(!tree)
        return;
    printLeafInOrder(tree->left);
    if (!tree->left && !tree->right)
        printf("%d ", tree->key);
    printLeafInOrder(tree->right);
}

// 13
void printNonLeafInOrder(Tree tree){
    if(!tree)
        return;
    printNonLeafInOrder(tree->left);
    if (tree->left || tree->right)
        printf("%d ", tree->key);
    printNonLeafInOrder(tree->right);
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
    int f = 1, key = 0, cnt = 0;
    while (f){
        printf("0. exit\n");
        printf("1. find node in tree\n");
        printf("2. height\n");
        printf("3. depth\n");
        printf("4. mirror\n");
        printf("5. clone\n");
        printf("6. isIdentical\n");
        printf("7. delete tree\n");
        printf("8. find predecessor\n");
        printf("9. find successor\n");
        printf("10. count leaf nodes\n");
        printf("11. count non leaf nodes\n");
        printf("12. print leaf nodes inorder\n");
        printf("13. print non leaf nodes inorder\n");
        printf("14. print tree\n\n");

        printf("enter choice: ");
        scanf("%d", &f);

        switch (f)
        {
        case 1:
            printf("enter key: ");
            scanf("%d", &key);
            out = findNode(tree, key);
            printTree(out);
            break;
        case 2:
            key = height(tree);
            printf("%d\n", key);
            break;
        case 3:
            key = depth(tree);
            printf("%d\n", key);
            break;
        case 4:
            out = mirror(tree);
            printTree(out);
            break;
        case 5:
            out = clone(tree);
            printTree(out);
            break;
        case 6:
            key = isIdentical(tree, out);
            printf("%d\n", key);
            break;
        case 7:
            deleteBinaryTree(tree);
            break;
        case 8:
            out = findSuccessor(tree);
            printTree(out);
            break;
        case 9:
            out = findPredecessor(tree);
            printTree(out);
            break;
        case 10:
            cnt = countLeafNodes(tree);
            printf("%d\n", cnt);
            break;
        case 11:
            cnt = countNonLeafNodes(tree);
            printf("%d\n", cnt);
            break;
        case 12:
            printLeafInOrder(tree);
            break;
        case 13:
            printNonLeafInOrder(tree);
            break;
        case 14:
            printTree(tree);
            break;
        default:
            break;
        }
    }
    return 0;
}
