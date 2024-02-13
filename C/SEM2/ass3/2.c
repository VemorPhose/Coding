#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n = 3;

typedef struct student_t {
    char *name;
    int roll;
    float cpi;
} student_t;

void InsSort(int *arr, int n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

student_t **expandArr(student_t **p){
    n = ceil(n * 1.2);
    student_t **p_new = (student_t**) realloc(p, n*sizeof(student_t*));
    return p_new;
}

student_t **shortenArr(student_t **p){
    n = ceil(n * 0.75);
    student_t **p_new = (student_t**) realloc(p, n*sizeof(student_t*));
    return p_new;
}

void display(student_t **p, int m){
    for(int i = 0; i < m; i++){
        printf("%s %d %f\n\n", (*p+i)->name, (*p+i)->roll, (*p+i)->cpi);
    }
}

void pushback(student_t **p, int *m){
    student_t *temp = (student_t*) calloc(1, sizeof(student_t));
    printf("enter name: ");
    scanf("%s", &temp->name);
    printf("enter roll no: ");
    scanf("%d", &temp->roll);
    printf("enter cpi: ");
    scanf("%f", &temp->cpi);
    *(p + *m) = temp;
    *m += 1;
}

void pushfront(student_t **p, int *m){
    student_t *temp = (student_t*) calloc(1, sizeof(student_t));
    printf("enter name: ");
    scanf("%s", &temp->name);
    printf("enter roll no: ");
    scanf("%d", &temp->roll);
    printf("enter cpi: ");
    scanf("%f", &temp->cpi);
    for(int i = (*m)-1; i >= 0; i--)
        *(p+i+1) = *(p+i);
    *p = temp;
    *m += 1;
}

void pushati(student_t **p, int *m, int ind){
    student_t *temp = (student_t*) calloc(1, sizeof(student_t));
    printf("enter name: ");
    scanf("%s", &temp->name);
    printf("enter roll no: ");
    scanf("%d", &temp->roll);
    printf("enter cpi: ");
    scanf("%f", &temp->cpi);
    for(int i = (*m)-1; i >= ind; i--)
        *(p+i+1) = *(p+i);
    *(p + ind) = temp;
    *m += 1;
}

int main(){
    student_t **arr = (student_t**) calloc(n, sizeof(student_t*));
    student_t **p = arr;

    int m = 0;
    int flag = 1;
    while(flag){
        printf("0. exit\n");
        printf("1. push_back\n");
        printf("2. push_front\n");
        printf("3. insert at i\n");
        printf("4. pop_back\n");
        printf("5. pop_front\n");
        printf("6. remove from i\n");
        printf("7. sort by roll\n");
        printf("8. sort by cpi\n");
        printf("9. display all\n");
        printf("\nenter choice: ");
        scanf("%d", &flag);
        fflush(stdin);

        if(flag == 0) break;

        else if(flag == 1){
            if(m >= n) p = expandArr(p);
            pushback(p, &m);
        }

        else if(flag == 2){
            if(m >= n) p = expandArr(p);
            pushfront(p, &m);
        }

        else if(flag == 3){
            if(m >= n) p = expandArr(p);
            printf("enter index to input at: ");
            int ind = 0;
            scanf("%d", &ind);
            fflush(stdin);
            pushati(p, &m, ind);
        }

        printf("\n%d %d\n", m, n);
        display(p, m);
    }

    return 0;
}
