#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

typedef struct graph_t *Graph;
typedef int Type;
typedef struct node_t *Node;

struct graph_t {
    int v, e;
    Node *adj;
};

struct node_t
{
    Type data;
    Node next;
};

// Type data = 0;
// int status = 1;

Node newNode(Node next, Type data){
    Node nNode = (Node) calloc(1, sizeof(struct node_t));
    nNode->data = data;
    nNode->next = next;
    return nNode;
}

Node addFirst(Node node, Type data){
    return newNode(node, data);
}

void printList(Node node){
    for(; node; node = node->next)
        printf("%d->", node->data);
    printf("NULL\n");
    // printf("data = %d, status = %d\n", data, status);
    return;
}

// directed graph
int main() {
    Graph graph = (Graph) calloc (1, sizeof(struct graph_t));
    scanf("%d", &(graph->v));
    scanf("%d", &(graph->e));
    graph->adj = (Node*) calloc (graph->v, sizeof(Node));
    for(int cnt_v = 0; cnt_v < graph->v; cnt_v++)
        graph->adj[cnt_v] = NULL;

    int i = 0, j = 0;
    for(int cnt_e = 0; cnt_e < graph->e; cnt_e++){
        scanf("%d", &i);
        scanf("%d", &j);
        graph->adj[i] = addFirst(graph->adj[i], j);
    }

    for(i = 0; i < graph->v; i++){
        printf("%d: ", i);
        printList(graph->adj[i]);
    }
    return 0;
}


