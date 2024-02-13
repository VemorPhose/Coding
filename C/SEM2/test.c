#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct node_t *Node;

struct node_t
{
    Type data;
    Node next;
};

Type data = NULL;
int status = 1;

Node newNode(Node next, Type data){
    Node nNode = (Node) calloc(1, sizeof(struct node_t));
    nNode->data = data;
    nNode->next = next;
    return nNode;
}

Node addFirst(Node node, Type data){
    return newNode(node, data);
}

int countListElements(Node node){
    int cnt = 0;
    for(; node; node = node->next, cnt++);
    return cnt;
}

Type findElement(Node node, int index){
    int cnt = countListElements(node);
    if(!node || index >= cnt || (-1)*index > cnt){
        status = 0;
        return 0;
    }
    status = 1;
    if(index < 0) index += cnt;
    for(int i = 0; i < index; i++, node = node->next);
    return node->data;
}

void printList(Node node){
    for(; node; node = node->next)
        printf("%d->", node->data);
    printf("NULL\n");
    printf("data = %d, status = %d\n", data, status);
    return;
}

int main(){
    Node list = NULL;
    list = addFirst(list, 1);
    list = addFirst(list, 3);
    list = addFirst(list, 4);
    list = addFirst(list, 2);
    list = addFirst(list, -4);
    printList(list);
    int index = 0;
    for(int i = 0; i < 10; i++){
        printf("enter index to find: ");
        scanf("%d", &index);
        int temp = findElement(list, index);
        printf("element at index %d is %d, status is %d\n", index, temp, status);
    }

    return 0;
}
