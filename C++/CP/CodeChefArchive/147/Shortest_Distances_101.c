#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

typedef struct queue_t *Queue;
typedef struct graph_t *Graph;

struct queue_t {
    int *array;
    unsigned int capacity;
    int front, rear;
};

struct graph_t {
    int v, e;
    bool **adj;
    bool *visited;
    int *dist;
};

Queue newQueue(unsigned int capacity){
    Queue queue = (Queue) calloc (1, sizeof(struct queue_t));
    assert(queue);
    queue->array = (int*) calloc (capacity, sizeof(int));
    assert(queue->array);
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
}

bool isEmpty(Queue queue){
    return queue->front == -1 && queue->rear == -1;
}

bool isFull(Queue queue){
    return queue->rear - queue->front == queue->capacity - 1;
}

bool enqueue(Queue queue, int data){
    if(isFull(queue)) return 0;
    if(isEmpty(queue)){
        queue->front = queue->rear = 0;
        queue->array[queue->front] = data;
    }
    else{
        ++queue->rear;
        queue->array[queue->rear%queue->capacity] = data;
    }
    return 1;
}

bool dequeue(Queue queue, int *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front];
    queue->array[(queue->front++)%queue->capacity] = 0;
    if(queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return 1;
}

void bfs(Graph graph, int vertex){
    Queue queue = newQueue(graph->v);
    enqueue(queue, vertex);
    graph->visited[vertex] = 1;
    graph->dist[vertex] = 0;

    while(!isEmpty(queue)){
        int cur_vertex = vertex;
        dequeue(queue, &cur_vertex);
        printf("at %d, dist. %d\n", cur_vertex, graph->dist[cur_vertex]);
        for(int child = 0; child < graph->v; child++){
            if(!graph->visited[child] && graph->adj[cur_vertex][child]){
                enqueue(queue, child);
                graph->visited[child] = 1;
                graph->dist[child] = graph->dist[cur_vertex] + 1;
            }
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, q;
        scanf("%d %d", &n, &q);
        Graph graph = (Graph) calloc (1, sizeof(struct graph_t));
        // printf("enter number of vertices: ");
        graph->v = n;
        // printf("enter number of edges: ");
        graph->e = q;
        graph->adj = (bool**) calloc (graph->v, sizeof(bool*));
        for(int cnt_v = 0; cnt_v < graph->v; cnt_v++)
            graph->adj[cnt_v] = (bool*) calloc (graph->v, sizeof(bool));
        graph->visited = (bool*) calloc (graph->v, sizeof(bool));
        graph->dist = (int*) calloc (graph->v, sizeof(int));

        int i = 0, j = 0;
        // printf("enter %d edges as space separated vertex-pairs: \n", graph->e);
        for(int cnt_e = 0; cnt_e < graph->e; cnt_e++){
            scanf("%d", &i);
            scanf("%d", &j);
            graph->adj[i][j] = 1;
        }
    }


    
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
    // printf("enter vertex of graph to start bfs from: ");
    scanf("%d", &vertex);
    bfs(graph, vertex);

    return 0;
}