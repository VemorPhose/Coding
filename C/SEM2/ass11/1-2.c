#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

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
	tree->right = buildTreeHelperInPost(post, in, index+1, inEnd, postIndex);
	tree->left = buildTreeHelperInPost(post, in, inStart, index-1, postIndex);
	return tree;
}

Tree buildTreeInPost(int post[], int in[], int n){
	int inStart = 0;
	int inEnd = n-1;
	int postIndex = n-1;
	
	return buildTreeHelperInPost(post, in, inStart, inEnd, &postIndex);
}

Tree buildTreeHelperInPre(int pre[], int in[], int inStart, int inEnd, int *preIndex){
	if (inStart>inEnd) return NULL;
	Tree tree =  newTree(NULL, pre[*preIndex], NULL, NULL);
	(*preIndex)++;
	int index = linearSearch(in, inStart, inEnd, tree->key);
	tree->left = buildTreeHelperInPre(pre, in, inStart, index-1, preIndex);
	tree->right = buildTreeHelperInPre(pre, in, index+1, inEnd, preIndex);
	return tree;
}

Tree buildTreeInPre(int pre[], int in[], int n){
	int inStart = 0;
	int inEnd = n-1;
	int preIndex = 0;
	
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