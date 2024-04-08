#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

typedef struct graph_t *Graph;

struct graph_t {
    int v, e;
    bool **adj;
    bool *visited;
};

void dfs(Graph graph, int vertex){
    printf("%d\n", vertex);
    graph->visited[vertex] = 1;
    for(int child = 0; child < graph->v; child++){
        if(!graph->visited[child] && graph->adj[vertex][child])
            dfs(graph, child);
    }
}

int main() {
    Graph graph = (Graph) calloc (1, sizeof(struct graph_t));
    // printf("enter number of vertices: ");
    scanf("%d", &(graph->v));
    // printf("enter number of edges: ");
    scanf("%d", &(graph->e));
    graph->adj = (bool**) calloc (graph->v, sizeof(bool*));
    for(int cnt_v = 0; cnt_v < graph->v; cnt_v++)
        graph->adj[cnt_v] = (bool*) calloc (graph->v, sizeof(bool));
    graph->visited = (bool*) calloc (graph->v, sizeof(bool));

    int i = 0, j = 0;
    // printf("enter %d edges as space separated vertex-pairs: \n", graph->e);
    for(int cnt_e = 0; cnt_e < graph->e; cnt_e++){
        scanf("%d", &i);
        scanf("%d", &j);
        graph->adj[i][j] = 1;
    }

    // printf("adjacency matrix is: \n");
    for(i = 0; i < graph->v; i++){
        for(j = 0; j < graph->v; j++){
            printf("%d ", graph->adj[i][j]);
        }
        printf("\n");
    }

    int vertex;
    // printf("enter vertex of graph to start dfs from: ");
    scanf("%d", &vertex);
    dfs(graph, vertex);

    return 0;
}