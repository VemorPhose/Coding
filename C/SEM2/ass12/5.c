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

    if (l <= heap->heap_size && heap->A[l] > heap->A[largest])
        largest = l;
    if (r <= heap->heap_size && heap->A[r] > heap->A[largest])
        largest = r;
    if (largest != i){
        swap(heap->A + i, heap->A + largest);
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(Heap heap){
    for (int i = heap->heap_size / 2; i > 0; i--)
        maxHeapify(heap, i);
}

void insert(Heap heap, int key){
    if(heap->heap_size == heap->length){
        printf("max size reached\n");
        return;
    }
    heap->heap_size += 1;
    heap->A[heap->heap_size] = key;
    buildMaxHeap(heap);
}

int getMax(Heap heap){
    int returnee =  heap->A[1];
    heap->A[1] = 0;
    swap(heap->A + 1, heap->A + heap->heap_size);
    heap->heap_size -= 1;
    maxHeapify(heap, 1);
    return returnee;
}

int main (){
    Heap heap = (Heap) calloc (1, sizeof(struct heap_t));
    int cin;
    scanf("%d", &cin);
    heap->length = cin;
    heap->heap_size = 0;
    heap->A = (int*) calloc (heap->length + 1, sizeof(int));

    for(int i = 0; i < cin; i++){
        int temp; scanf("%d", &temp);
        insert(heap, temp);
    }

    for(int i = 1; i <= heap->heap_size; i++)
        printf("%d ", *(heap->A + i));
    printf("\n");

    for(int i = 0; i < cin; i++){
        printf("%d\n", getMax(heap));
        for(int i = 1; i <= heap->heap_size; i++)
            printf("%d ", *(heap->A + i));
        printf("\n");
    }

    return 0;
}