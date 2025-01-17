<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Type;
typedef struct Node_t *Node;

struct Node_t
{
    Node prev;
    Type data;
    Node next;
};

Type data = 0;
int status = 1;

Node newNode(Node prev, Type data, Node next){
    Node node = (Node) calloc(1, sizeof(struct Node_t));
    assert(node);
    node->prev = prev;
    node->data = data;
    node->next = next;
    return node;
}

// 1
Node addFirst(Node node, Type data){
    if(!node){
        node = newNode(NULL, data, NULL);
        node->next = node->prev = node;
        return node;
    }
    node = newNode(node->prev, data, node);
    node->prev->next = node->next->prev = node;
    return node;
}

// 2
void printList(Node node){
    printf("data = %d, status = %d\n", data, status);
    if(!node){
        printf("NULL\n");
        return;
    }
    Node p;
    for(; p->next != node; p = p->next)
        printf("%d->", p->data);
    printf("%d\n", p->data);
    for(; p != node; p = p->prev)
        printf("%d<-", p->data);
    printf("%d\n", p->data);
    return;
}

// 3
int countListElements(Node node){
    if(!node) return 0;
    int cnt = 1;
    Node p = node;
    for(; p->next != node; p = p->next, cnt++);
    return cnt;
}

// 4
Node removeFirst(Node node){
    if(!node){
        status = 0;
        return node;
    }
    status = 1;
    data = node->data;
    if(node->next == node){
        node->next = node->prev = NULL;
        free(node);
        return NULL;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Node p = node->next;
    node->next = node->prev = NULL;
    free(node);
    return p;
}

// 5
Node addLast(Node node, Type data){
    return addFirst(node, data)->next;
}

// 6
Node removeLast(Node node){
    if(!node) return removeFirst(node);
    return removeFirst(node->prev);
}

// 7
Node addAtIndex(Node node, Type data, int index){
    if(index > countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == countListElements(node))
        return addLast(node, data);
    if(index == 0)
        return addFirst(node, data);
    Node p = node;
    for(; index > 0; index--, p = p->next);
    p = addFirst(p, data);
    return node;
}

// 8
Node removeAtIndex(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == countListElements(node)-1)
        return removeLast(node);
    if(index == 0)
        return removeFirst(node);
    Node p = node;
    for(; index > 0; index--, p = p->next);
    p = removeFirst(p);
    return node;
}

// 9
void addAfterFirstOccurence(Node node, Type data, Type key){
    if(!node){
        status = 0;
        return;
    }
    Node p = node;
    for(; p->data != key && p->next != node; p = p->next);
    if(p->data != key){
        status = 0;
        return;
    }
    status = 1;
    p = addFirst(p->next, data);
    return;
}

// 10
Node removeFirstOccurence(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    if(node->data == key){
        status = 1;
        return removeFirst(node);
    }
    Node p = node;
    for(; p->data != key && p->next != node; p = p->next);
    if(p->data != key){
        status = 0;
        return node;
    }
    status = 1;
    p = removeFirst(p);
    return node;
}

// 11
Node reverseList(Node node){
    Node newList = NULL;
    Node p = node;
    for(; p->next != node; p = p->next)
        newList = addFirst(newList, p->data);
    newList = addFirst(newList, p->data);
    for(int i = 0; i < countListElements(node); i++)
        node = removeFirst(node);
    return newList;
}

// 12
Node reverseListNoNewList(Node node){
    if (!node) return node;
    Node p = node;
    for(; p->next != node; p = p->next){
        Node temp = p->next;
        p->next = p->prev;
        p->prev = temp;
    }
    Node temp = p->next;
    p->next = p->prev;
    p->prev = temp;
    return node->next;
}

// 13
Node insertInSortedList(Node node, Type data){
    if(!node || node->data >= data)
        return addFirst(node, data);
    if(node->prev->data <= data)
        return addLast(node, data);
    Node p = node;
    for(; p->next != node && p->data < data; p = p->next);
    if(p->data >= data)
        p = addFirst(p, data);
    return node;
}

// 14
Node sortList(Node node){
    Node newList = addFirst(NULL, node->data);
    Node p = node->next;
    for(; p != node; p = p->next)
        insertInSortedList(newList, p->data);
    for(int i = 0; i < countListElements(node); i++)
        node = removeFirst(node);
    return newList;
}

// 15
Node mergeLists(Node node1, Node node2){
    if(!node2) return node1;
    Node p = node2;
    for(; p->next != node2; p = p->next)
        node1 = addLast(node1, p->data);
    node1 = addLast(node1, p->data);
    for(int i = 0; i < countListElements(node2); i++)
        node2 = removeFirst(node2);
    return node1;
}

// 16
Type findInList(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return 0;
    }
    for(int i = 0; i < index; i++, node = node->next);
    status = 1;
    return node->data;
}

// 17
Node mergeListsSorted(Node node1, Node node2){
    node1 = mergeLists(node1, node2);
    node1 = sortList(node1);
    return node1;
}

// 18
void printListRecursive(Node node, Node p){
    if(!node){
        printf("NULL\n");
        return;
    }
    if(p->next == node){
        printf("%d\n", p->data);
        return;
    }
    printf("%d->", p->data);
    printListRecursive(node, p->next);
    return;
}

// 19
void printListRecursiveReverse(Node node, Node p){
    if(!node){
        printf("NULL\n");
        return;
    }
    node = node->prev;
    p = p->prev;
    if(p->prev == node){
        printf("%d<-%d\n", p->data, p->prev->data);
        return;
    }
    printf("%d<-", p->data);
    printListRecursive(node, p->prev);
    return;
}

// 20
Node reverseListRecursive(Node node, Node p){
    if(!node) return node;
    if(p->next == node){
        Node temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        return p;
    }
    Node temp = p->next;
    p->next = p->prev;
    p->prev = temp;
    return reverseListRecursive(node, temp);
}

// 21
Node rectifyPrev(Node node){
    if(!node) return node;
    Node p = node;
    Node prev = NULL;
    for(; p->next != node; p = p->next){
        p->next->prev = p;
    }
    p->next->prev = p;
    return node;
}

// 22
Node rotateClockwise(Node node, int n){
    int l = countListElements(node);
    n = n%l;
    for(int i = 0; i < n; i++)
        node = node->prev;
    return node;
}

// eval 2
Node removeAllVal(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    int cnt = countListElements(node);
    int flag = 0;
    for(int i = 0; i < cnt; i++){
        if(node->data == key){
            node = removeFirst(node);
            flag = 1;
        }
        else
            node = node->next;
    }
    status = flag;
    return node;
}

// eval 3
Node removeEvenOddNodes(Node node, int mode){
    int cnt = countListElements(node);
    if(!cnt || (cnt == 1 && !mode)){
        status = 0;
        return node;
    }
    if(cnt == 1 && mode&1){
        return removeFirst(node);
    }
    if(mode&1){
        if(cnt&1){
            for(int i = 0; i < cnt/2; i++){
                node = removeFirst(node);
                node = node->next;
            }
            return removeFirst(node);
        }
        for(int i = 0; i < (cnt+1)/2; i++){
            node = removeFirst(node);
            node = node->next;
        }
        return node;
    }
    if(cnt&1){
        for(int i = 0; i < cnt/2; i++){
            node = node->next;
            node = removeFirst(node);
        }
        return node->next;
    }
    for(int i = 0; i < cnt/2; i++){
        node = node->next;
        node = removeFirst(node);
    }
    return node;
}

int main(){
    Node list = NULL;
    Node list2 = NULL;
    int f = 0;
    int index = 0;
    Type element = 0;
    Type key = 0;
    int mode = 0;

    do{
        printf("0. exit\n");
        printf("1. add element to beginning\n");
        //printf("2. print list\n");
        // printf("3. count number of elements\n");
        printf("4. remove first element\n");
        // printf("5. add element at end\n");
        // printf("6. remove last element\n");
        // printf("7. add element at index\n");
        // printf("8. remove element at index\n");
        // printf("9. add element after first occurence of an element\n");
        // printf("10. remove first occurence of an element\n");
        // printf("11. reverse list\n");
        // printf("12. reverse list no new list\n");
        // printf("13. insert into sorted list\n");
        // printf("14. sort list\n");
        // printf("15. merge lists\n");
        // printf("16. find at index\n");
        // printf("17. merge sorted lists\n");
         printf("18. print list recursively\n");
        // printf("19. print list in reverse order recursively\n");
        // printf("20. reverse list recursively\n");
        // printf("21. rectify prev pointers\n");
        // printf("22. rotate clockwise\n");
        printf("23. remove all elements of value\n");
        printf("24. remove odd(1) or even(0) elements\n");

        printf("\nenter choice: ");
        scanf("%d", &f);
        if(f==1||f==5||f==7||f==9||f==13){
            printf("enter element to be added: ");
            scanf("%d", &element);
        }
        if(f==7||f==8||f==16){
            printf("enter index of element: ");
            scanf("%d", &index);
        }
        if(f==9||f==10||f==23){
            printf("enter element to find: ");
            scanf("%d", &key);
        }

        switch(f){
            case 1:
                list = addFirst(list, element);
                break;
            case 2:
                printList(list);
                break;
            case 3:
                printf("no. of elements in list is/are %d\n", countListElements(list));
                break;
            case 4:
                list = removeFirst(list);
                if(!status) printf("failed to remove any elements\n");
                break;
            case 5:
                list = addLast(list, element);
                break;
            case 6:
                list = removeLast(list);
                break;
            case 7:
                list = addAtIndex(list, element, index);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 8:
                list = removeAtIndex(list, index);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 9:
                addAfterFirstOccurence(list, element, key);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 10:
                list = removeFirstOccurence(list, key);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 11:
                list = reverseList(list);
                break;
            case 12:
                list = reverseListNoNewList(list);
                break;
            case 13:
                list = insertInSortedList(list, element);
                break;
            case 14:
                list = sortList(list);
                break;
            case 15:
                list = mergeLists(list, list2);
                break;
            case 16:
                element = findInList(list, index);
                if(!status) printf("failed to find element\n");
                else printf("element at index %d is %d\n", index, element);
                break;
            case 17:
                list = mergeListsSorted(list, list2);
                break;
            case 18:
                printf("data = %d, status = %d\n", data, status);
                printListRecursive(list, list);
                break;
            case 19:
                printListRecursiveReverse(list, list);
                break;
            case 20:
                list = reverseListRecursive(list, list);
                break;
            case 21:
                list = rectifyPrev(list);
                break;
            case 22:
                printf("enter number of times to rotate: ");
                scanf("%d", &index);
                list = rotateClockwise(list, index);
                break;
            case 23:
                list = removeAllVal(list, key);
                if(!status) printf("failed to remove any elements\n");
                break;
            case 24:
                printf("0: even, 1: odd : ");
                scanf("%d", &mode);
                list = removeEvenOddNodes(list, mode);
                if(!status) printf("failed to remove any elements\n");
                break;
            default:
                break;
        }
    } while(f);

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Type;
typedef struct Node_t *Node;

struct Node_t
{
    Node prev;
    Type data;
    Node next;
};

Type data = 0;
int status = 1;

Node newNode(Node prev, Type data, Node next){
    Node node = (Node) calloc(1, sizeof(struct Node_t));
    assert(node);
    node->prev = prev;
    node->data = data;
    node->next = next;
    return node;
}

// 1
Node addFirst(Node node, Type data){
    if(!node){
        node = newNode(NULL, data, NULL);
        node->next = node->prev = node;
        return node;
    }
    node = newNode(node->prev, data, node);
    node->prev->next = node->next->prev = node;
    return node;
}

// 2
void printList(Node node){
    printf("data = %d, status = %d\n", data, status);
    if(!node){
        printf("NULL\n");
        return;
    }
    Node p;
    for(; p->next != node; p = p->next)
        printf("%d->", p->data);
    printf("%d\n", p->data);
    for(; p != node; p = p->prev)
        printf("%d<-", p->data);
    printf("%d\n", p->data);
    return;
}

// 3
int countListElements(Node node){
    if(!node) return 0;
    int cnt = 1;
    Node p = node;
    for(; p->next != node; p = p->next, cnt++);
    return cnt;
}

// 4
Node removeFirst(Node node){
    if(!node){
        status = 0;
        return node;
    }
    status = 1;
    data = node->data;
    if(node->next == node){
        node->next = node->prev = NULL;
        free(node);
        return NULL;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Node p = node->next;
    node->next = node->prev = NULL;
    free(node);
    return p;
}

// 5
Node addLast(Node node, Type data){
    return addFirst(node, data)->next;
}

// 6
Node removeLast(Node node){
    if(!node) return removeFirst(node);
    return removeFirst(node->prev);
}

// 7
Node addAtIndex(Node node, Type data, int index){
    if(index > countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == countListElements(node))
        return addLast(node, data);
    if(index == 0)
        return addFirst(node, data);
    Node p = node;
    for(; index > 0; index--, p = p->next);
    p = addFirst(p, data);
    return node;
}

// 8
Node removeAtIndex(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return node;
    }
    status = 1;
    if(index == countListElements(node)-1)
        return removeLast(node);
    if(index == 0)
        return removeFirst(node);
    Node p = node;
    for(; index > 0; index--, p = p->next);
    p = removeFirst(p);
    return node;
}

// 9
void addAfterFirstOccurence(Node node, Type data, Type key){
    if(!node){
        status = 0;
        return;
    }
    Node p = node;
    for(; p->data != key && p->next != node; p = p->next);
    if(p->data != key){
        status = 0;
        return;
    }
    status = 1;
    p = addFirst(p->next, data);
    return;
}

// 10
Node removeFirstOccurence(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    if(node->data == key){
        status = 1;
        return removeFirst(node);
    }
    Node p = node;
    for(; p->data != key && p->next != node; p = p->next);
    if(p->data != key){
        status = 0;
        return node;
    }
    status = 1;
    p = removeFirst(p);
    return node;
}

// 11
Node reverseList(Node node){
    Node newList = NULL;
    Node p = node;
    for(; p->next != node; p = p->next)
        newList = addFirst(newList, p->data);
    newList = addFirst(newList, p->data);
    for(int i = 0; i < countListElements(node); i++)
        node = removeFirst(node);
    return newList;
}

// 12
Node reverseListNoNewList(Node node){
    if (!node) return node;
    Node p = node;
    for(; p->next != node; p = p->next){
        Node temp = p->next;
        p->next = p->prev;
        p->prev = temp;
    }
    Node temp = p->next;
    p->next = p->prev;
    p->prev = temp;
    return node->next;
}

// 13
Node insertInSortedList(Node node, Type data){
    if(!node || node->data >= data)
        return addFirst(node, data);
    if(node->prev->data <= data)
        return addLast(node, data);
    Node p = node;
    for(; p->next != node && p->data < data; p = p->next);
    if(p->data >= data)
        p = addFirst(p, data);
    return node;
}

// 14
Node sortList(Node node){
    Node newList = addFirst(NULL, node->data);
    Node p = node->next;
    for(; p != node; p = p->next)
        insertInSortedList(newList, p->data);
    for(int i = 0; i < countListElements(node); i++)
        node = removeFirst(node);
    return newList;
}

// 15
Node mergeLists(Node node1, Node node2){
    if(!node2) return node1;
    Node p = node2;
    for(; p->next != node2; p = p->next)
        node1 = addLast(node1, p->data);
    node1 = addLast(node1, p->data);
    for(int i = 0; i < countListElements(node2); i++)
        node2 = removeFirst(node2);
    return node1;
}

// 16
Type findInList(Node node, int index){
    if(index >= countListElements(node)){
        status = 0;
        return 0;
    }
    for(int i = 0; i < index; i++, node = node->next);
    status = 1;
    return node->data;
}

// 17
Node mergeListsSorted(Node node1, Node node2){
    node1 = mergeLists(node1, node2);
    node1 = sortList(node1);
    return node1;
}

// 18
void printListRecursive(Node node, Node p){
    if(!node){
        printf("NULL\n");
        return;
    }
    if(p->next == node){
        printf("%d\n", p->data);
        return;
    }
    printf("%d->", p->data);
    printListRecursive(node, p->next);
    return;
}

// 19
void printListRecursiveReverse(Node node, Node p){
    if(!node){
        printf("NULL\n");
        return;
    }
    node = node->prev;
    p = p->prev;
    if(p->prev == node){
        printf("%d<-%d\n", p->data, p->prev->data);
        return;
    }
    printf("%d<-", p->data);
    printListRecursive(node, p->prev);
    return;
}

// 20
Node reverseListRecursive(Node node, Node p){
    if(!node) return node;
    if(p->next == node){
        Node temp = p->next;
        p->next = p->prev;
        p->prev = temp;
        return p;
    }
    Node temp = p->next;
    p->next = p->prev;
    p->prev = temp;
    return reverseListRecursive(node, temp);
}

// 21
Node rectifyPrev(Node node){
    if(!node) return node;
    Node p = node;
    Node prev = NULL;
    for(; p->next != node; p = p->next){
        p->next->prev = p;
    }
    p->next->prev = p;
    return node;
}

// 22
Node rotateClockwise(Node node, int n){
    int l = countListElements(node);
    n = n%l;
    for(int i = 0; i < n; i++)
        node = node->prev;
    return node;
}

// eval 2
Node removeAllVal(Node node, Type key){
    if(!node){
        status = 0;
        return node;
    }
    int cnt = countListElements(node);
    int flag = 0;
    for(int i = 0; i < cnt; i++){
        if(node->data == key){
            node = removeFirst(node);
            flag = 1;
        }
        else
            node = node->next;
    }
    status = flag;
    return node;
}

// eval 3
Node removeEvenOddNodes(Node node, int mode){
    int cnt = countListElements(node);
    if(!cnt || (cnt == 1 && !mode)){
        status = 0;
        return node;
    }
    if(cnt == 1 && mode&1){
        return removeFirst(node);
    }
    if(mode&1){
        if(cnt&1){
            for(int i = 0; i < cnt/2; i++){
                node = removeFirst(node);
                node = node->next;
            }
            return removeFirst(node);
        }
        for(int i = 0; i < (cnt+1)/2; i++){
            node = removeFirst(node);
            node = node->next;
        }
        return node;
    }
    if(cnt&1){
        for(int i = 0; i < cnt/2; i++){
            node = node->next;
            node = removeFirst(node);
        }
        return node->next;
    }
    for(int i = 0; i < cnt/2; i++){
        node = node->next;
        node = removeFirst(node);
    }
    return node;
}

int main(){
    Node list = NULL;
    Node list2 = NULL;
    int f = 0;
    int index = 0;
    Type element = 0;
    Type key = 0;
    int mode = 0;

    do{
        printf("0. exit\n");
        printf("1. add element to beginning\n");
        //printf("2. print list\n");
        // printf("3. count number of elements\n");
        printf("4. remove first element\n");
        // printf("5. add element at end\n");
        // printf("6. remove last element\n");
        // printf("7. add element at index\n");
        // printf("8. remove element at index\n");
        // printf("9. add element after first occurence of an element\n");
        // printf("10. remove first occurence of an element\n");
        // printf("11. reverse list\n");
        // printf("12. reverse list no new list\n");
        // printf("13. insert into sorted list\n");
        // printf("14. sort list\n");
        // printf("15. merge lists\n");
        // printf("16. find at index\n");
        // printf("17. merge sorted lists\n");
         printf("18. print list recursively\n");
        // printf("19. print list in reverse order recursively\n");
        // printf("20. reverse list recursively\n");
        // printf("21. rectify prev pointers\n");
        // printf("22. rotate clockwise\n");
        printf("23. remove all elements of value\n");
        printf("24. remove odd(1) or even(0) elements\n");

        printf("\nenter choice: ");
        scanf("%d", &f);
        if(f==1||f==5||f==7||f==9||f==13){
            printf("enter element to be added: ");
            scanf("%d", &element);
        }
        if(f==7||f==8||f==16){
            printf("enter index of element: ");
            scanf("%d", &index);
        }
        if(f==9||f==10||f==23){
            printf("enter element to find: ");
            scanf("%d", &key);
        }

        switch(f){
            case 1:
                list = addFirst(list, element);
                break;
            case 2:
                printList(list);
                break;
            case 3:
                printf("no. of elements in list is/are %d\n", countListElements(list));
                break;
            case 4:
                list = removeFirst(list);
                if(!status) printf("failed to remove any elements\n");
                break;
            case 5:
                list = addLast(list, element);
                break;
            case 6:
                list = removeLast(list);
                break;
            case 7:
                list = addAtIndex(list, element, index);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 8:
                list = removeAtIndex(list, index);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 9:
                addAfterFirstOccurence(list, element, key);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 10:
                list = removeFirstOccurence(list, key);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 11:
                list = reverseList(list);
                break;
            case 12:
                list = reverseListNoNewList(list);
                break;
            case 13:
                list = insertInSortedList(list, element);
                break;
            case 14:
                list = sortList(list);
                break;
            case 15:
                list = mergeLists(list, list2);
                break;
            case 16:
                element = findInList(list, index);
                if(!status) printf("failed to find element\n");
                else printf("element at index %d is %d\n", index, element);
                break;
            case 17:
                list = mergeListsSorted(list, list2);
                break;
            case 18:
                printf("data = %d, status = %d\n", data, status);
                printListRecursive(list, list);
                break;
            case 19:
                printListRecursiveReverse(list, list);
                break;
            case 20:
                list = reverseListRecursive(list, list);
                break;
            case 21:
                list = rectifyPrev(list);
                break;
            case 22:
                printf("enter number of times to rotate: ");
                scanf("%d", &index);
                list = rotateClockwise(list, index);
                break;
            case 23:
                list = removeAllVal(list, key);
                if(!status) printf("failed to remove any elements\n");
                break;
            case 24:
                printf("0: even, 1: odd : ");
                scanf("%d", &mode);
                list = removeEvenOddNodes(list, mode);
                if(!status) printf("failed to remove any elements\n");
                break;
            default:
                break;
        }
    } while(f);

    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
