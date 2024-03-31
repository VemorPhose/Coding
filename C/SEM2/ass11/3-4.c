#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    int height;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode *tn;

int height(tn node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalance(tn node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

tn newNode(int val) {
    tn node = (tn)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}

tn rightRotate(tn y) {
    tn x = y->left;
    tn T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

tn leftRotate(tn x) {
    tn y = x->right;
    tn T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

tn insert(tn node, int val) {
    
    if (node == NULL){
        return newNode(val);
    }
    if (val < node->val){
        node->left = insert(node->left, val);
    }
    else if (val > node->val){
        node->right = insert(node->right, val);
    }
    else{
        return node;
    }
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);
    //ll
    if (balance > 1 && val < node->left->val)
        return rightRotate(node);

    //rr
    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    //lr
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //rl
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

tn minValueNode(tn node) {
    tn current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

tn deleteNode(tn root, int val) {
    if (root == NULL)
        return root;

    if (val < root->val)
        root->left = deleteNode(root->left, val);
    else if (val > root->val)
        root->right = deleteNode(root->right, val);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            tn temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } 
            else{
                *root = *temp;
            }

            free(temp);
        } 
        else{
            tn temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
    }
    if (root == NULL){
        return root;
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
    int balance = getBalance(root);

    //ll
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    //lr
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //rr 
        if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    //rl
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


void inOrder(tn root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

int main() {
    tn root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Inorder traversal of the constructed AVL tree is: ");
    inOrder(root);
    printf("\n");

    return 0;
}