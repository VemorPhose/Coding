#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct node_t *Node;
typedef struct list_t *List;

struct node_t
{
    Node prev;
    Type data;
    Node next;
};

Node newNode(Node prev, Type data, Node next){
    Node node = (Node) calloc(1, sizeof(struct node_t));
    node->prev = prev;
    node->data = data;
    node->next = next;
    return node;
}

// 1
void addFirst(Node *pHead, Node *pTail, Type data){
    *pHead = newNode(NULL, data, *pHead);
    if(!*pTail) *pTail = *pHead;
    if((*pHead)->next)
        (*pHead)->next->prev = *pHead;
}

// 2
void printList(Node head, Node tail, Type data, int status){
    if(!head){
        printf("NULL\n");
        printf("data = %d, status = %d\n", data, status);
        return;
    }
    printf("NULL->");
    for(; head; head = head->next)
        printf("%d->", head->data);
    printf("NULL\n");
    printf("NULL<-");
    for(; tail; tail = tail->prev)
        printf("%d<-", tail->data);
    printf("NULL\n");
    printf("data = %d, status = %d\n", data, status);
}

// 3
int countListElements(Node head){
    int cnt = 0;
    for(; head; head = head->next, cnt++);
    return cnt;
}

// 4
int removeFirst(Node *pHead, Node *pTail, Type *data){
    if(countListElements(*pHead) == 0)
        return 0;
    if(countListElements(*pHead) == 1){
        *data = (*pHead)->data;
        free(*pHead);
        *pHead = *pTail = NULL;
        return 1;
    }
    Node temp = *pHead;
    *pHead = (*pHead)->next;
    (*pHead)->prev = NULL;
    temp->next = NULL;
    *data = temp->data;
    free(temp);
    return 1;
}

// 5
void addLast(Node *pHead, Node *pTail, Type data){
    if(!*pHead){
        addFirst(pHead, pTail, data);
        return;
    }
    (*pTail)->next = newNode(*pTail, data, NULL);
    *pTail = (*pTail)->next;
}

// 6
int removeLast(Node *pHead, Node *pTail, Type *data){
    if(countListElements(*pHead) == 0)
        return 0;
    if(countListElements(*pHead) == 1){
        return removeFirst(pHead, pTail, data);
    }
    Node temp = *pTail;
    *pTail = (*pTail)->prev;
    (*pTail)->next = NULL;
    temp->prev = NULL;
    *data = temp->data;
    free(temp);
    return 1;
}

// 7
int addAtIndex(Node *pHead, Node *pTail, Type data, int index){
    if(index > countListElements(*pHead) || index < 0)
        return 0;
    if(index == 0){
        addFirst(pHead, pTail, data);
        return 1;
    }
    if(index == countListElements(*pHead)){
        addLast(pHead, pTail, data);
        return 1;
    }
    Node p = *pHead;
    for(int i = 0; i < index - 1; i++)
        p = p->next;
    Node node = newNode(p, data, p->next);
    p->next = p->next->prev = node;
    return 1;
}

// 8
int removeAtIndex(Node *pHead, Node *pTail, Type *data, int index){
    if(index >= countListElements(*pHead) || index < 0)
        return 0;
    if(index == 0)
        return removeFirst(pHead, pTail, data);
    if(index == countListElements(*pHead) - 1)
        return removeLast(pHead, pTail, data);
    Node p = *pHead;
    for(int i = 0; i < index - 1; i++)
        p = p->next;
    Node node = p->next;
    p->next->next->prev = p;
    p->next = p->next->next;
    node->prev = node->next = NULL;
    *data = node->data;
    free(node);
    return 1;
}

// 9
int addAfterFirstOccurence(Node *pHead, Node *pTail, Type data, Type key){
    if(!*pHead)
        return 0;
    Node p = *pHead;
    for(; p->data != key && p->next; p = p->next);
    if(p->data != key)
        return 0;
    Node node = newNode(p, data, p->next);
    if(p->next)
        p->next = p->next->prev = node;
    else{
        p->next = node;
        *pTail = p->next;
    }
    return 1;
}

// 10
int removeFirstOccurence(Node *pHead, Node *pTail, Type *data, Type key){
    if(!*pHead)
        return 0;
    if((*pHead)->data == key){
        return removeFirst(pHead, pTail, data);
    }
    if(!(*pHead)->next)
        return 0;
    Node p = *pHead;
    for(; p->next->data != key && p->next->next; p = p->next);
    if(p->next->data != key)
        return 0;
    Node node = p->next;
    if(p->next->next)
        p->next->next->prev = p;
    else
        *pTail = p;
    p->next = p->next->next;
    *data = node->data;
    node->next = node->prev = NULL;
    free(node);
    return 1;
}

// 11
void reverseList(Node *pHead, Node *pTail){
    Node p = *pHead;
    Type buf;
    Node headNew = NULL;
    Node tailNew = NULL;
    for(; *pHead;){
        addFirst(&headNew, &tailNew, (*pHead)->data);
        removeFirst(pHead, pTail, &buf);
    }
    *pHead = headNew;
    *pTail = tailNew;
}

int main(){
    Node head = NULL;
    Node tail = NULL;
    Type data = 0;
    int status = 1;
    addFirst(&head, &tail, 2);
    addFirst(&head, &tail, 4);
    addFirst(&head, &tail, 3);
    printList(head, tail, data, status);
    printf("no. of elements: %d\n", countListElements(head));
    status = removeFirst(&head, &tail, &data);
    printList(head, tail, data, status);
    status = removeFirst(&head, &tail, &data);
    printList(head, tail, data, status);
    removeFirst(&head, &tail, &data);
    printList(head, tail, data, status);
    // printf("%p\n%p\n", head, tail);
    addFirst(&head, &tail, 2);
    addFirst(&head, &tail, 4);
    addFirst(&head, &tail, 3);
    addLast(&head, &tail, 5);
    printList(head, tail, data, status);
    addAtIndex(&head, &tail, 6, 2);
    printList(head, tail, data, status);
    addAfterFirstOccurence(&head, &tail, 7, 6);
    addAfterFirstOccurence(&head, &tail, 7, 3);
    addAfterFirstOccurence(&head, &tail, 7, 5);
    printList(head, tail, data, status);
    removeAtIndex(&head, &tail, &data, 4);
    printList(head, tail, data, status);
    removeAtIndex(&head, &tail, &data, 0);
    printList(head, tail, data, status);
    removeAtIndex(&head, &tail, &data, 5);
    printList(head, tail, data, status);
    removeFirstOccurence(&head, &tail, &data, 7);
    printList(head, tail, data, status);
    removeFirstOccurence(&head, &tail, &data, 6);
    printList(head, tail, data, status);
    removeFirstOccurence(&head, &tail, &data, 5);
    printList(head, tail, data, status);
    reverseList(&head, &tail);
    printList(head, tail, data, status);

    return 0;
}

