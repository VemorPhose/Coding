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
void reverseListNewList(Node *pHead, Node *pTail){
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

// 12
void reverseList(Node *pHead, Node *pTail){
    Node p = *pHead;
    for(; p; p = p->prev){
        Node temp = p->next;
        p->next = p->prev;
        p->prev = temp;
    }
    Node temp = *pHead;
    *pHead = *pTail;
    *pTail = temp;
}

// 13
void insertInSortedList(Node *pHead, Node *pTail, Type data){
    if(!*pHead || (*pHead)->data > data){
        addFirst(pHead, pTail, data);
        return;
    }
    if((*pTail)->data <= data){
        addLast(pHead, pTail, data);
        return;
    }
    Node p = *pHead;
    for(; p->next; p = p->next){
        if(p->data <= data && p->next->data >= data){
            Node node = newNode(p, data, p->next);
            p->next = p->next->prev = node;
            return;
        }
    }
    Node node = newNode(p, data, p->next);
    p->next = p->next->prev = node;
    return;
}

// 14
void sortList(Node *pHead, Node *pTail){
    Node headNew = NULL;
    Node tailNew = NULL;
    Type buf;
    while(*pHead){
        insertInSortedList(&headNew, &tailNew, (*pHead)->data);
        removeFirst(pHead, pTail, &buf);
    }
    *pHead = headNew;
    *pTail = tailNew;
}

// 15
void mergeLists(Node *pHead1, Node *pTail1, Node *pHead2, Node *pTail2){
    (*pTail1)->next = *pHead2;
    (*pHead2)->prev = *pTail1;
    *pTail1 = *pTail2;
}

// 16
int getAtIndex(Node *pHead, Node *pTail, Type *data, int index){
    if(index >= countListElements(*pHead))
        return 0;
    Node p = *pHead;
    for(int i = 0; i < index; i++)
        p = p->next;
    *data = p->data;
    return 1;
}

// 17
void mergeSort(Node *pHead1, Node *pTail1, Node *pHead2, Node *pTail2){
    mergeLists(pHead1, pTail1, pHead2, pTail2);
    sortList(pHead1, pTail1);
}

// 18
void printListRecursive(Node head, Node tail){
    if(head == NULL && tail == NULL){
        printf("NULL\n");
        return;
    }
    if(head == tail){
        printf("%d\n", head->data);
        return;
    }
    printf("%d -> ", head->data);
    printListRecursive(head->next, tail);
}

// 19
void printListRecursiveReverse(Node head, Node tail){
    if(head == NULL && tail == NULL){
        printf("NULL\n");
        return;
    }
    if(head == tail){
        printf("%d\n", tail->data);
        return;
    }
    printf("%d <- ", tail->data);
    printListRecursiveReverse(head, tail->prev);
}

// 20
void reverseListRecursive(Node *pHead, Node *pTail, Node head){
    if(!*pHead && !*pTail)
        return;
    if(!head){
        Node temp = *pHead;
        *pHead = *pTail;
        *pTail = temp;
        return;
    }
    Node temp = head->next;
    head->next = head->prev;
    head->prev = temp;
    reverseListRecursive(pHead, pTail, head->prev);
}

int main(){
    Node head = NULL;
    Node tail = NULL;
    Node head2 = NULL;
    Node tail2 = NULL;
    Type data = 0;
    int status = 1;
    int index = 0;
    int f = 1;
    Type key = 0;

    do{
        printf("0. exit\n");
        printf("1. add element to beginning\n");
        printf("2. print list\n");
        printf("3. count number of elements\n");
        printf("4. remove first element\n");
        printf("5. add element at end\n");
        printf("6. remove last element\n");
        printf("7. add element at index\n");
        printf("8. remove element at index\n");
        printf("9. add element after first occurence of an element\n");
        printf("10. remove first occurence of an element\n");
        printf("11. reverse list\n");
        printf("12. reverse list no new list\n");
        printf("13. insert into sorted list\n");
        printf("14. sort list\n");
        printf("15. merge lists\n");
        printf("16. find at index\n");
        printf("17. merge sorted lists\n");
        printf("18. print list recursively\n");
        printf("19. print list in reverse order recursively\n");
        printf("20. reverse list recursively\n");

        printf("\nenter choice: ");
        scanf("%d", &f);
        if(f==1||f==5||f==7||f==9||f==13){
            printf("enter element to be added: ");
            scanf("%d", &data);
        }
        if(f==7||f==8||f==16){
            printf("enter index of element: ");
            scanf("%d", &index);
        }
        if(f==9||f==10){
            printf("enter element to find: ");
            scanf("%d", &key);
        }

        switch(f){
            case 1:
                addFirst(&head, &tail, data);
                break;
            case 2:
                printList(head, tail, data, status);
                break;
            case 3:
                printf("no. of elements in list is/are %d\n", countListElements(head));
                break;
            case 4:
                status = removeFirst(&head, &tail, &data);
                break;
            case 5:
                addLast(&head, &tail, data);
                break;
            case 6:
                status = removeLast(&head, &tail, &data);
                break;
            case 7:
                status = addAtIndex(&head, &tail, data, index);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 8:
                status = removeAtIndex(&head, &tail, &data, index);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 9:
                status = addAfterFirstOccurence(&head, &tail, data, key);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 10:
                status = removeFirstOccurence(&head, &tail, &data, key);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 11:
                reverseListNewList(&head, &tail);
                break;
            case 12:
                reverseList(&head, &tail);
                break;
            case 13:
                insertInSortedList(&head, &tail, data);
                break;
            case 14:
                sortList(&head, &tail);
                break;
            case 15:
                mergeLists(&head, &tail, &head2, &tail2);
                break;
            case 16:
                status = getAtIndex(&head, &tail, &data, index);
                if(!status) printf("failed to find element\n");
                else printf("element at index %d is %d\n", index, data);
                break;
            case 17:
                mergeSort(&head, &tail, &head2, &tail2);
                break;
            case 18:
                printListRecursive(head, tail);
                break;
            case 19:
                printListRecursiveReverse(head, tail);
                break;
            case 20:
                reverseListRecursive(&head, &tail, head);
                break;
            default:
                break;
        }
    } while(f);

    return 0;
}

