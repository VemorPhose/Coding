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
    if(node->next = node){
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
        return;
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
    Node cur = node;
    Node prev = NULL;
    Node next = NULL;
    while (cur->next != node) {
        next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    return prev;
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

void printListRecursive(Node node){
    if(!node){
        printf("NULL\n");
        return;
    }
    printf("%d->", node->data);
    printListRecursive(node->next);
    return;
}

void printListRecursiveReverse(Node node, int flag){
    if(!node){
        printf("NULL");
        return;
    }
    printListRecursiveReverse(node->next, 0);
    printf("<-%d", node->data);
    if(flag) printf("\n");
    return;
}

Node reverseListRecursive(Node node){
    static Node newList = NULL;
    if(node == NULL) return newList;
    newList = addFirst(newList, node->data);
    Node temp = node->next;
    node->next = NULL;
    free(node);
    reverseListRecursive(temp);
    return newList;
}

int main(){
    Node list = NULL;
    int f = 0;
    int index = 0;
    Type element = 0;
    Type key = 0;

    do{
        printf("0. exit\n");
        printf("1. add element to beginning\n");
        printf("2. print list\n");
        printf("3. count number of elements\n");
        printf("4. remove first element\n");
        printf("5. add element at end\n");
        printf("6. remove last element\n");
        printf("7. get an element at index\n");
        printf("8. set an element at index\n");
        printf("9. add an element at index\n");
        printf("10. remove an element at index\n");
        printf("11. add element after first occurence of an element\n");
        printf("12. remove first occurence of an element\n");
        printf("13. reverse list\n");
        printf("14. insert element into a sorted list\n");
        printf("15. sort list\n");
        printf("16. print list recursively\n");
        printf("17. print list in reverse order recursively\n");
        printf("18. reverse list recursively\n");

        printf("\nenter choice: ");
        scanf("%d", &f);
        if(f==1||f==5||f==8||f==9||f==11||f==14){
            printf("enter element to be added/set: ");
            scanf("%d", &element);
        }
        if(f==7||f==8||f==9||f==10){
            printf("enter index of element to be added/removed: ");
            scanf("%d", &index);
        }
        if(f==11||f==12){
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
                break;
            case 5:
                list = addLast(list, element);
                break;
            case 6:
                list = removeLast(list);
                break;
            case 7:
                data = findIndex(list, index);
                if(status) printf("element is %d\n", data);
                else printf("index invalid\n");
                break;
            case 8:
                setIndex(list, element, index);
                if(status) printf("set element successfully\n");
                else printf("failed to set element\n");
                break;
            case 9:
                list = addAtIndex(list, element, index);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 10:
                list = removeAtIndex(list, index);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 11:
                addAfterFirstOccurence(list, element, key);
                if(status) printf("added element successfully\n");
                else printf("failed to add element\n");
                break;
            case 12:
                list = removeFirstOccurence(list, key);
                if(status) printf("removed element successfully\n");
                else printf("failed to remove element\n");
                break;
            case 13:
                list = reverseList(list);
                break;
            case 14:
                list = insertInSortedList(list, element);
                break;
            case 15:
                list = sortList(list);
                break;
            case 16:
                printListRecursive(list);
                break;
            case 17:
                printListRecursiveReverse(list, 1);
                break;
            case 18:
                list = reverseListRecursive(list);
                break;
            default:
                break;
        }
    } while(f);

    return 0;
}