#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int ukey;
    char title[100]; 
    char issn[20]; 
} book_t;

typedef struct {
    int roll; 
    char name[100]; 
} student_t;


typedef struct Node {
    void *data; 
    int isBook; 
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} LinkedList;


LinkedList *createLinkedList();
void insertData(LinkedList *list);
void deleteAtIndex(LinkedList *list, size_t index);
void *getAtIndex(LinkedList *list, size_t index);
size_t length(LinkedList *list);
void printList(LinkedList *list);
void sortList(LinkedList *list, int sortBy);
int compareBooksByUkey(const void *a, const void *b);
int compareBooksByISSN(const void *a, const void *b);
int compareStudentsByRoll(const void *a, const void *b);
void printBook(const void *data);
void printStudent(const void *data);
void freeLinkedList(LinkedList *list);


int main() {
    LinkedList *dataList = createLinkedList();

    int choice;
    do {
        printf("\nEnter your choice:\n");
        printf("1. Add Book\n");
        printf("2. Add Student\n");
        printf("3. Print Data\n");
        printf("4. Sort by ukey\n");
        printf("5. Sort by ISSN\n");
        printf("6. Sort by student roll\n");
        printf("7. Get length of list\n");
        printf("8. Delete at index\n");
        printf("9. Get data at index\n");
        printf("10. Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertData(dataList);
                break;
            case 2:
                insertData(dataList);
                break;
            case 3:
                printf("\nData:\n");
                printList(dataList);
                break;
            case 4:
                sortList(dataList, 1);
                break;
            case 5:
                sortList(dataList, 2);
                break;
            case 6:
                sortList(dataList, 3);
                break;
            case 7:
                printf("Length of list: %zu\n", length(dataList));
                break;
            case 8:
                printf("Enter index to delete: ");
                size_t delIndex;
                scanf("%zu", &delIndex);
                deleteAtIndex(dataList, delIndex);
                break;
            case 9:
                printf("Enter index to get data: ");
                size_t getIndex;
                scanf("%zu", &getIndex);
                void *data = getAtIndex(dataList, getIndex);
                if (data != NULL) {
                    if (((Node *)data)->isBook)
                        printBook(((Node *)data)->data);
                    else
                        printStudent(((Node *)data)->data);
                } else {
                    printf("Invalid index or data not found.\n");
                }
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
                break;
        }
    } while (choice != 10);
    
    freeLinkedList(dataList);
    return 0;
}


LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertData(LinkedList *list) {
    if (list == NULL) {
        return;
    }

    int choice;
    printf("Enter your choice:\n");
    printf("1. Add Book\n");
    printf("2. Add Student\n");
    scanf("%d", &choice);

    void *data;
    if (choice == 1) {
        book_t *book = (book_t *)malloc(sizeof(book_t));
        printf("Enter Book Details:\n");
        printf("ukey: ");
        scanf("%d", &book->ukey);
        printf("Title: ");
        scanf("%s", book->title);
        printf("ISSN: ");
        scanf("%s", book->issn);
        data = (void *)book;
    } else if (choice == 2) {
        student_t *student = (student_t *)malloc(sizeof(student_t));
        printf("Enter Student Details:\n");
        printf("Roll: ");
        scanf("%d", &student->roll);
        printf("Name: ");
        scanf("%s", student->name);
        data = (void *)student;
    } else {
        printf("Invalid choice.\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->isBook = (choice == 1) ? 1 : 0;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void deleteAtIndex(LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        printf("Invalid index or empty list.\n");
        return;
    }

    Node *current = list->head;
    Node *prev = NULL;

    size_t i = 0;
    while (current != NULL && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Index out of range.\n");
        return;
    }

    if (prev == NULL) {
        list->head = current->next;
    } 
    else {
        prev->next = current->next;
    }
    
    free(current->data); 
    free(current);
    list->size--;
}

void *getAtIndex(LinkedList *list, size_t index) {
    if (list == NULL || index >= list->size) {
        printf("Invalid index or empty list.\n");
        return NULL;
    }

    Node *current = list->head;

    size_t i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Index out of range.\n");
        return NULL;
    }

    return current;
}  


size_t length(LinkedList *list) {
    return list->size;
}


void printList(LinkedList *list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        if (current->isBook) {
            printBook(current->data);
        } 
        
        else {
            printStudent(current->data);
        }
        current = current->next;
    }
}

void sortList(LinkedList *list, int sortBy) {
    if (list == NULL || list->head == NULL || list->size <= 1) {
        printf("List is empty or contains only one element. No sorting needed.\n");
        return;
    }

    Node *current = list->head;
    Node *index = NULL;
    void *temp;

    if (sortBy == 1) {
        for (current = list->head; current != NULL; current = current->next) {
            for (index = current->next; index != NULL; index = index->next) {
                if (((book_t *)(current->data))->ukey > ((book_t *)(index->data))->ukey) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
            }
        }
        printf("List sorted by ukey.\n");
    } 
    
    else if (sortBy == 2) {
        for (current = list->head; current != NULL; current = current->next) {
            for (index = current->next; index != NULL; index = index->next) {
                if (strcmp(((book_t *)(current->data))->issn, ((book_t *)(index->data))->issn) > 0) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
            }
        }
        printf("List sorted by ISSN.\n");
    } 
    
    else if (sortBy == 3) {
        for (current = list->head; current != NULL; current = current->next) {
            for (index = current->next; index != NULL; index = index->next) {
                if (((student_t *)(current->data))->roll > ((student_t *)(index->data))->roll) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
            }
        }
        printf("List sorted by student roll.\n");
    } 
    
    else {
        printf("Invalid sort option.\n");
    }
}

void printBook(const void *data) {
    const book_t *book = (const book_t *)data;
    printf("Book - ukey: %d, Title: %s, ISSN: %s\n", book->ukey, book->title, book->issn);
}

void printStudent(const void *data) {
    const student_t *student = (const student_t *)data;
    printf("Student - Roll: %d, Name: %s\n", student->roll, student->name);
}

void freeLinkedList(LinkedList *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current); 
        current = next;
    }

    free(list);
}