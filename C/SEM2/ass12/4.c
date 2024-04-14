#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

struct heap_t{
    int *A;
    int length;
    int heap_size;
};

typedef struct heap_t *Heap;

int parent(int i){
    return i / 2;
}

int left(int i){
    return 2 * i;
}

int right(int i){
    return 2 * i + 1;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Heap heap, int i){
    int largest = i;
    int l = left(i);
    int r = right(i);
    // printf("i = %d, l = %d, r = %d\n", i, l, r);

    if (l <= heap->heap_size && heap->A[l] > heap->A[largest]){
        // printf("largest = l\n");
        largest = l;
    }
    if (r <= heap->heap_size && heap->A[r] > heap->A[largest]){
        // printf("largest = r\n");
        largest = r;
    }
    if (largest != i){
        swap(heap->A + i, heap->A + largest);
        // for(int i = 1; i <= heap->length; i++)
        //     printf("%d ", *(heap->A + i));
        // printf("\n");
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(Heap heap){
    heap->heap_size = heap->length;
    for (int i = heap->length / 2; i > 0; i--)
        maxHeapify(heap, i);
}

void heapSort(Heap heap){
    buildMaxHeap(heap);
    for(int i = heap->length; i > 0; i--){
        swap(heap->A + i, heap->A + 1);
        // for(int i = 1; i <= heap->length; i++)
        //     printf("%d ", *(heap->A + i));
        // printf("\n");
        heap->heap_size -= 1;
        maxHeapify(heap, 1);
    }
}

int main (){
    Heap heap = (Heap) calloc (1, sizeof(struct heap_t));
    int cin;
    scanf("%d", &cin);
    heap->length = cin;
    heap->A = (int*) calloc (heap->length + 1, sizeof(int));
    for(int i = 1; i <= heap->length; i++)
        scanf("%d", (heap->A + i));

    for(int i = 1; i <= heap->length; i++)
        printf("%d ", *(heap->A + i));
    printf("\n");

    heapSort(heap);
    for(int i = 1; i <= heap->length; i++)
        printf("%d ", *(heap->A + i));
    printf("\n");

    return 0;
}