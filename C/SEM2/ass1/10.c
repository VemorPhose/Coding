#include <stdio.h>
typedef struct node_t {
int data;
struct node_t *next;
} Node_t, *Node;
void f(Node_t *h) {
h ? printf("%d -> ", h->data), f(h->next) : printf("NULL");
}
void g(Node_t *h) {
h ? g(h->next), printf(" <- %d", h->data) : printf("NULL");
}
int main() {
Node_t n4 = {4, 0}, n3 = {3, &n4}, n2 = {2, &n3}, n1 = {1, &n2};
Node h = &n1;
f(h);
printf("\n");
g(h);
return 0;
}
