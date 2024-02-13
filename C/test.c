#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct node_t *Node;

struct node_t
{
    Type data;
    Node next; 
};

Type data = 0;
int status = 1;

Node newNode(Node next, Type data){
    Node nNode = (Node) calloc(1, sizeof(struct node_t));
    nNode->data = data;
    nNode->next = next;
    return nNode;
}

Node addFirst(Node node, Type data){
    return newNode(node, data);
}

Node addLast(Node node, Type data){
    if(!node){
        return addFirst(node, data);
    }
    Node pLast = node;
    for(; pLast->next; pLast = pLast->next);
    pLast->next = newNode(NULL, data);
    return node;
}

int main(){
    Node list = NULL;
    
    return 0;
}