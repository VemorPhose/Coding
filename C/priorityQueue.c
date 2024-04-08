#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

// Priority queue maintains S elements, each with a 'key'.

// max/min-priority-queue.

// maxPriorityQueue:
//     insert(S, x) --> inserts x into set S.
//     maximum(S) --> returns element of S with max key.
//     extractMax(S) --> 