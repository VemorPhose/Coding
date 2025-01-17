<<<<<<< HEAD
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

void printList(Node node){
    for(; node; node = node->next)
        printf("%d->", node->data);
    printf("NULL\n");
    printf("data = %d, status = %d\n", data, status);
    return;
}

int countListElements(Node node){
    int cnt = 0;
    for(; node; node = node->next, cnt++);
    return cnt;
}

Node removeFirst(Node node){
    if(!node){
        status = 0;
        return node;
    }
    status = 1;
    data = node->data;
    Node newList = node->next;
    node->next = NULL;
    free(node);
    return newList;
}

Node addLast(Node node, Type data){
    if(!node){
        return addFirst(node, data);
    }
    Node pLast = node;
    for(; pLast->next; pLast = pLast->next);
    pLast->next = newNode(NULL, data);
    return node;
}

Node removeLast(Node node){
    if(!node || !node->next){
        return removeFirst(node);
    }
    status = 1;
    Node pLast = node;
    for(; pLast->next->next; pLast = pLast->next);
    data = pLast->next->data;
    free(pLast->next);
    pLast->next = NULL;
    return node;
}

Type findIndex(Node node, int index){
    if(!node){
        status = 0;
        return NULL;
    }
    int cnt = 0;
    for(; cnt < index && node->next; node = node->next, cnt++);
    if(cnt == index){
        status = 1;
        data = node->data;
        return node->data;
    }
    status = 0;
    return NULL;
}

void setIndex(Node node, Type data, int index){
    if(!node){
        status = 0;
        return;
    }
    int cnt = 0;
    for(; cnt < index && node->next; node = node->next, cnt++);
    if(cnt == index){
        status = 1;
        node->data = data;
        return;
    }
    status = 0;
    return;
}

Node addAtIndex(Node node, Type data, int index){
    if(index == 0){
        status = 1;
        return addFirst(node, data);
    }
    if(!node) return node;
    int cnt = 0;
    Node pTemp = node;
    for(; cnt < index-1 && pTemp->next->next; pTemp = pTemp->next, cnt++);
    if(cnt == index-1){
        status = 1;
        pTemp->next = newNode(pTemp->next, data);
        return node;
    }
    if(index == countListElements(node)){
        status = 1;
        return addLast(node, data);
    }
    status = 0;
    return node;
}

Node removeAtIndex(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == 0)
        return removeFirst(node);
    int cnt = 0;
    Node pTemp = node;
    for(; cnt < index-1 && pTemp->next->next; pTemp = pTemp->next, cnt++);
    Node temp = pTemp->next->next;
    pTemp->next->next = NULL;
    data = pTemp->next->data;
    free(pTemp->next);
    pTemp->next = temp;
    return node;
}

void addAfterFirstOccurence(Node node, Type data, Type key){
    if(!node){
        status = 0;
        return;
    }
    for(; node->data != key && node->next; node = node->next);
    if(node->data != key){
        status = 0;
        return;
    }
    status = 1;
    node->next = newNode(node->next, data);
    return;
}

Node removeFirstOccurence(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    if(node->data == key){
        return removeFirst(node);
    }
    if(!node->next){
        status = 0;
        return node;
    }
    Node pTemp = node;
    for(; pTemp->next->data != key && pTemp->next->next; pTemp = pTemp->next);
    if(pTemp->next->data != key){
        status = 0;
        return node;
    }
    status = 1;
    Node temp = pTemp->next->next;
    pTemp->next->next = NULL;
    data = pTemp->next->data;
    free(pTemp->next);
    pTemp->next = temp;
    return node;
}

Node reverseList(Node node){
    Node newList;
    newList->data = node->data;
    newList->next = NULL;
}

int main(){
    Node list = NULL;
    list = addFirst(list, 2);
    list = addFirst(list, 4);
    list = addFirst(list, 4);
    list = removeFirst(list);
    printList(list);
    list = addLast(list, 6);
    list = addLast(list, 7);
    list = removeLast(list);
    printList(list);
    printf("no. of elements = %d\n", countListElements(list));
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    setIndex(list, 3, 1);
    printList(list);
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    list = addAtIndex(list, 2, 1);
    printList(list);
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    list = addAtIndex(list, 9, 0);
    printList(list);
    list = addAtIndex(list, 7, 4);
    printList(list);
    list = addAtIndex(list, 8, 6);
    printList(list);
    list = removeAtIndex(list, 0);
    printList(list);
    list = removeAtIndex(list, 1);
    printList(list);
    list = removeAtIndex(list, 2);
    printList(list);
    list = removeAtIndex(list, 3);
    printList(list);
    addAfterFirstOccurence(list, 9, 6);
    printList(list);
    addAfterFirstOccurence(list, 4, 5);
    printList(list);
    addAfterFirstOccurence(list, 5, 4);
    printList(list);
    list = removeFirstOccurence(list, 7);
    printList(list);
    list = removeFirstOccurence(list, 9);
    printList(list);
    list = removeFirstOccurence(list, 3);
    printList(list);
    list = removeFirstOccurence(list, 4);
    printList(list);

    return 0;
}
=======
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

void printList(Node node){
    for(; node; node = node->next)
        printf("%d->", node->data);
    printf("NULL\n");
    printf("data = %d, status = %d\n", data, status);
    return;
}

int countListElements(Node node){
    int cnt = 0;
    for(; node; node = node->next, cnt++);
    return cnt;
}

Node removeFirst(Node node){
    if(!node){
        status = 0;
        return node;
    }
    status = 1;
    data = node->data;
    Node newList = node->next;
    node->next = NULL;
    free(node);
    return newList;
}

Node addLast(Node node, Type data){
    if(!node){
        return addFirst(node, data);
    }
    Node pLast = node;
    for(; pLast->next; pLast = pLast->next);
    pLast->next = newNode(NULL, data);
    return node;
}

Node removeLast(Node node){
    if(!node || !node->next){
        return removeFirst(node);
    }
    status = 1;
    Node pLast = node;
    for(; pLast->next->next; pLast = pLast->next);
    data = pLast->next->data;
    free(pLast->next);
    pLast->next = NULL;
    return node;
}

Type findIndex(Node node, int index){
    if(!node){
        status = 0;
        return NULL;
    }
    int cnt = 0;
    for(; cnt < index && node->next; node = node->next, cnt++);
    if(cnt == index){
        status = 1;
        data = node->data;
        return node->data;
    }
    status = 0;
    return NULL;
}

void setIndex(Node node, Type data, int index){
    if(!node){
        status = 0;
        return;
    }
    int cnt = 0;
    for(; cnt < index && node->next; node = node->next, cnt++);
    if(cnt == index){
        status = 1;
        node->data = data;
        return;
    }
    status = 0;
    return;
}

Node addAtIndex(Node node, Type data, int index){
    if(index == 0){
        status = 1;
        return addFirst(node, data);
    }
    if(!node) return node;
    int cnt = 0;
    Node pTemp = node;
    for(; cnt < index-1 && pTemp->next->next; pTemp = pTemp->next, cnt++);
    if(cnt == index-1){
        status = 1;
        pTemp->next = newNode(pTemp->next, data);
        return node;
    }
    if(index == countListElements(node)){
        status = 1;
        return addLast(node, data);
    }
    status = 0;
    return node;
}

Node removeAtIndex(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == 0)
        return removeFirst(node);
    int cnt = 0;
    Node pTemp = node;
    for(; cnt < index-1 && pTemp->next->next; pTemp = pTemp->next, cnt++);
    Node temp = pTemp->next->next;
    pTemp->next->next = NULL;
    data = pTemp->next->data;
    free(pTemp->next);
    pTemp->next = temp;
    return node;
}

void addAfterFirstOccurence(Node node, Type data, Type key){
    if(!node){
        status = 0;
        return;
    }
    for(; node->data != key && node->next; node = node->next);
    if(node->data != key){
        status = 0;
        return;
    }
    status = 1;
    node->next = newNode(node->next, data);
    return;
}

Node removeFirstOccurence(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    if(node->data == key){
        return removeFirst(node);
    }
    if(!node->next){
        status = 0;
        return node;
    }
    Node pTemp = node;
    for(; pTemp->next->data != key && pTemp->next->next; pTemp = pTemp->next);
    if(pTemp->next->data != key){
        status = 0;
        return node;
    }
    status = 1;
    Node temp = pTemp->next->next;
    pTemp->next->next = NULL;
    data = pTemp->next->data;
    free(pTemp->next);
    pTemp->next = temp;
    return node;
}

Node reverseList(Node node){
    Node newList;
    newList->data = node->data;
    newList->next = NULL;
}

int main(){
    Node list = NULL;
    list = addFirst(list, 2);
    list = addFirst(list, 4);
    list = addFirst(list, 4);
    list = removeFirst(list);
    printList(list);
    list = addLast(list, 6);
    list = addLast(list, 7);
    list = removeLast(list);
    printList(list);
    printf("no. of elements = %d\n", countListElements(list));
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    setIndex(list, 3, 1);
    printList(list);
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    list = addAtIndex(list, 2, 1);
    printList(list);
    printf("data at index = %d, status = %d\n", findIndex(list, 1), status);
    list = addAtIndex(list, 9, 0);
    printList(list);
    list = addAtIndex(list, 7, 4);
    printList(list);
    list = addAtIndex(list, 8, 6);
    printList(list);
    list = removeAtIndex(list, 0);
    printList(list);
    list = removeAtIndex(list, 1);
    printList(list);
    list = removeAtIndex(list, 2);
    printList(list);
    list = removeAtIndex(list, 3);
    printList(list);
    addAfterFirstOccurence(list, 9, 6);
    printList(list);
    addAfterFirstOccurence(list, 4, 5);
    printList(list);
    addAfterFirstOccurence(list, 5, 4);
    printList(list);
    list = removeFirstOccurence(list, 7);
    printList(list);
    list = removeFirstOccurence(list, 9);
    printList(list);
    list = removeFirstOccurence(list, 3);
    printList(list);
    list = removeFirstOccurence(list, 4);
    printList(list);

    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
