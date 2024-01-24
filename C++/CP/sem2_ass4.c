#include <stdio.h>
#include <stdlib.h>

typedef int Type;
typedef struct node_t *Node;

struct node_t
{
    Type data;
    Node next;
};

Type data = 0;
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
        return 0;
    }
    int cnt = 0;
    for(; cnt < index && node->next; node = node->next, cnt++);
    if(cnt == index){
        status = 1;
        data = node->data;
        return node->data;
    }
    status = 0;
    return 0;
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
    Node newList = NULL;
    while(node){
        newList = addFirst(newList, node->data);
        Node temp = node->next;
        node->next = NULL;
        free(node);
        node = temp;
    }
    return newList;
}

Node insertInSortedList(Node node, Type data){
    if(!node || node->data > data)
        return addFirst(node, data);
    Node pTemp = node;
    for(; pTemp->next; pTemp = pTemp->next){
        if(pTemp->data <= data && pTemp->next->data >= data){
            pTemp->next = newNode(pTemp->next, data);
            return node;
        }
    }
    pTemp->next = newNode(pTemp->next, data);
    return node;
}

Node sortList(Node node){
    Node newList = NULL;
    while(node){
        newList = insertInSortedList(newList, node->data);
        Node temp = node->next;
        node->next = NULL;
        free(node);
        node = temp;
    }
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