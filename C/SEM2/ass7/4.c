#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t *Node;

struct node_t{
    int data;
    Node next;
};

Node newNode(Node node, int data){
    Node n = (Node) calloc (1, sizeof(struct node_t));
    n->data = data;
    n->next = node;
    return n;
}

Node addFirst(Node node, int data){
    return newNode(node, data);
}

int main(){
    Node p1 = NULL, p2 = NULL;
    char s1[1000], s2[1000];
    printf("Enter polynomial 1 coefficients from x0 to x20: ");
    for(int i = 0; i < 21; i++){
        int temp; scanf("%d", &temp);
        p1 = addFirst(p1, temp);
    }
    printf("Enter polynomial 2 coefficients from x0 to x20: ");
    for(int i = 0; i < 21; i++){
        int temp; scanf("%d", &temp);
        p2 = addFirst(p2, temp);
    }
    Node ptr = p1, qtr = p2;
    for(int i = 0; i < 21; i++){
        ptr->data += qtr->data;
        ptr = ptr->next;
        qtr = qtr->next;
    }
    ptr = p1;
    for(int i = 0; i < 21; i++){
        if(!ptr->data);
        else if(ptr->data > 0){
            printf("+%dx%d ", ptr->data, 20-i);
        }
        else printf("%dx%d ", ptr->data, 20-i);
        ptr = ptr->next;
    }
    printf("\n");
}