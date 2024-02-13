#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct student_t {
    char *name;
    int roll;
    float cpi;
} student_t;

typedef int(*cmp)(student_t *, student_t *);

int rollCmp(student_t *a, student_t *b){
    return a->roll > b->roll;
}

int cpiCmp(student_t *a, student_t *b){
    return a->cpi > b->cpi;
}

int m = 0;
int n = 3;

void insSort(student_t **ptr, cmp c){
    for(int i = 1; i < m; i++){
        student_t key;
        key.name = (char*) calloc(100, sizeof(char));
        key = *ptr[i];
        int j = i-1;
        while(j >= 0 && c(ptr[j], &key)){
            *ptr[j+1] = *ptr[j];
            j--;
        }
        *ptr[j+1] = key;
    }
}

student_t **expand(student_t **ptr);
student_t **contract(student_t **ptr);

void push_back(student_t **ptr);
void push_front(student_t **ptr);
void insert(student_t **ptr, int ind);

void pop_back(student_t **ptr);
void pop_front(student_t **ptr);
void delete(student_t **ptr, int ind);

void display(student_t **ptr);

int main(){
    student_t **ptr = (student_t**) calloc(3, sizeof(student_t*));
    int flag = 0;
    int ind = 0;
    // student_t *ram_ptr = (student_t*) calloc(1, sizeof(student_t));
    // scanf("%[^\n]%*c", ram_ptr->name);
    // printf("%s", ram_ptr->name);
    do {
        printf("\n0. exit\n");
        printf("1. insert at end\n");
        printf("2. insert at beginning\n");
        printf("3. insert at index\n");
        printf("4. delete from end\n");
        printf("5. delete from beginning\n");
        printf("6. delete at index\n");
        printf("7. sort by roll\n");
        printf("8. sort by cpi\n");
        printf("9. display all\n");
        
        printf("\nenter choice: ");
        scanf("%d", &flag);
        fflush(stdin);

        switch (flag){
            case 1:
                if(m >= n) ptr = expand(ptr);
                push_back(ptr);
                break;
            case 2:
                if(m >= n) ptr = expand(ptr);
                push_front(ptr);
                break;
            case 3:
                if(m >= n) ptr = expand(ptr);
                printf("enter index to insert at: ");
                scanf("%d", &ind);
                fflush(stdin);
                insert(ptr, ind);
                break;
            case 4:
                pop_back(ptr);
                if(m < n/2) ptr = contract(ptr);
                break;
            case 5:
                pop_front(ptr);
                if(m < n/2) ptr = contract(ptr);
                break;
            case 6:
                printf("enter index to delete from: ");
                scanf("%d", &ind);
                fflush(stdin);
                delete(ptr, ind);
                break;
            case 7:
                insSort(ptr, rollCmp);
                break;
            case 8:
                insSort(ptr, cpiCmp);
                break;
            case 9:
                display(ptr);
                break;
            default:
                break;
        }
    } while (flag);

    free(ptr);
    ptr = NULL;
    return 0;
}

student_t **expand(student_t **ptr){
    n = ceil(1.2 * n);
    student_t **ptr_new = (student_t**) realloc(ptr, n*sizeof(student_t*));
    return ptr_new;
}

student_t **contract(student_t **ptr){
    n = ceil(0.75 * n);
    student_t **ptr_new = (student_t**) realloc(ptr, n*sizeof(student_t*));
    return ptr_new;
}


void push_back(student_t **ptr){
    ptr[m] = (student_t*) calloc(1, sizeof(student_t));
    ptr[m]->name = (char*) calloc(100, sizeof(char));
    printf("enter name: ");
    scanf("%[^\n]%*c", ptr[m]->name);
    printf("enter roll: ");
    scanf("%d", &(ptr[m]->roll));
    printf("enter cpi: ");
    scanf("%f", &(ptr[m]->cpi));
    m++;
}

void push_front(student_t **ptr){
    ptr[m] = (student_t*) calloc(1, sizeof(student_t));
    ptr[m]->name = (char*) calloc(100, sizeof(char));
    for(int i = m-1; i >= 0; i--) *ptr[i+1] = *ptr[i];
    printf("enter name: ");
    ptr[0]->name = (char*) calloc(100, sizeof(char));
    scanf("%[^\n]%*c", ptr[0]->name);
    printf("enter roll: ");
    scanf("%d", &(ptr[0]->roll));
    printf("enter cpi: ");
    scanf("%f", &(ptr[0]->cpi));
    m++;
}
void insert(student_t **ptr, int ind){
    ptr[m] = (student_t*) calloc(1, sizeof(student_t));
    ptr[m]->name = (char*) calloc(100, sizeof(char));
    for(int i = m-1; i >= ind; i--) *ptr[i+1] = *ptr[i];
    printf("enter name: ");
    ptr[ind]->name = (char*) calloc(100, sizeof(char));
    scanf("%[^\n]%*c", ptr[ind]->name);
    printf("enter roll: ");
    scanf("%d", &(ptr[ind]->roll));
    printf("enter cpi: ");
    scanf("%f", &(ptr[ind]->cpi));
    m++;
}

void pop_back(student_t **ptr){
    m--;
    free(ptr[m]->name);
    free(ptr[m]);
    ptr[m] = NULL;
}

void pop_front(student_t **ptr){
    m--;
    free(ptr[0]->name);
    for(int i = 0; i < m; i++) *ptr[i] = *ptr[i+1];
    free(ptr[m]);
    ptr[m] = NULL;
}

void delete(student_t **ptr, int ind){
    m--;
    free(ptr[ind]->name);
    for(int i = ind; i < m; i++) *ptr[i] = *ptr[i+1];
    free(ptr[m]);
    ptr[m] = NULL;
}

void display(student_t **ptr){
    printf("m = %d && n = %d\n", m, n);
    for(int i = 0; i < m; i++){
        printf("%s %d %g\n", ptr[i]->name, ptr[i]->roll, ptr[i]->cpi);
    }
}