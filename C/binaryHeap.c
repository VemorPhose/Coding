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

// A.length --> total no. of elements
// A.heap_size --> no. of elements from front of Heap satisfying max/min-heap condition

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
    
    if (largest != i){
        int temp = heap->A[i];
        heap->A[i] = heap->A[largest];
        heap->A[largest] = heap->A[i];
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(Heap heap){
    heap->heap_size = heap->length;
    for (int i = heap->length / 2; i > 0; i--)
        maxHeapify(heap, i);
}

void heapSort(Heap heap){
    for(int i = heap->length; i >= 2; i--){
        int temp = heap->A[i];
        heap->A[i] = heap->A[1];
        heap->A[1] = heap->A[i];

        heap->heap_size -= 1;
        maxHeapify(heap, 0);
    }
}

// Time Complexity: Worst Case --> O(nlogn)

int main (){
    Heap heap = (Heap) calloc (1, sizeof(struct heap_t));
    int cin;
    printf("enter no. of elements in heap: ");
    scanf("%d", &cin);
    heap->length = cin;
    heap->A = (int*) calloc (heap->length + 1, sizeof(int));
    // Note array is 1-indexed.

    return 0;
}