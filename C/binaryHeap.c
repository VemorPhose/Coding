#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

// Binary tree stored in BFS traversal in an array is called a Binary Heap.
// All levels of Binary Tree are filled, except last level, which must be filled FROM THE LEFT.

// Properties of Nodes in Array:
//     Parent[i] == i/2
//     LeftChild[i] == 2i
//     RightChild[i] == 2i + 1

struct heap_t{
    int *A;
    int length;
    int heap_size;
};

typedef struct heap_t *Heap;

// max-heap: Every node is larger than its child nodes
// min-heap: Every node is smaller than its child nodes.

// A.length --> length of each Node element
// A.heap_size --> size of heap

// max-heapify --> For a node, if left and right subtree are max-heaps, checks and max-heapifies given node
//             --> checks max{node, left, right} and if left or right is max, swaps node with it.
//             --> recursively max-heapifies the largest node (if max is a child node)

int parent(int i){
    return i / 2;
}

int left(int i){
    return 2 * i;
}

int right(int i){
    return 2 * i + 1;
}

void maxHeapify(Heap heap, int i){
    int l = left(i);
    int r = right(i);
    int largest = i;
    if (l <= heap->heap_size && heap->A[l] > heap->A[r])
        largest = l;
    if (l <= heap->heap_size && heap->A[r] > heap->A[largest])
        largest = r;
}

int main (){
    Heap heap = (Heap) calloc (1, sizeof(struct heap_t));
    int cin;
    printf("enter no. of elements in heap: ");
    scanf("%d", &cin);
    heap->heap_size = cin;
    int cnt = 0;
    while(cin){
        cnt++;
        cin /= 2;
    }
    heap->length =  (int) pow(2, cnt) - 1;
    heap->A = (int*) calloc (heap->length, sizeof(int));

    return 0;
}