#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

typedef struct graph_t *Graph;

struct graph_t {
    int v, e;
    bool **adj;
};

// directed graph
int main() {
    Graph graph = (Graph) calloc (1, sizeof(struct graph_t));
    scanf("%d", &(graph->v));
    scanf("%d", &(graph->e));
    graph->adj = (bool**) calloc (graph->v, sizeof(bool*));
    for(int cnt_v = 0; cnt_v < graph->v; cnt_v++)
        graph->adj[cnt_v] = (bool*) calloc (graph->v, sizeof(bool));

    int i = 0, j = 0;
    for(int cnt_e = 0; cnt_e < graph->e; cnt_e++){
        scanf("%d", &i);
        scanf("%d", &j);
        graph->adj[i][j] = 1;
    }

    for(i = 0; i < graph->v; i++){
        for(j = 0; j < graph->v; j++){
            printf("%d ", graph->adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}
