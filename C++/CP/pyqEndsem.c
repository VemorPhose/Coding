#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pair{
    char ff[55];
    int ss;
} pair;

pair mp[1010];
int mpct = 0;

void mpInit();
void mpPrint();
void wspPara(char para[], int len);
void upperPara(char para[], int len);
void mapify(char para[], int len);
void mpSSsort();

int main(){
    // 1
    char para[50010];
    printf("Enter a paragraph in one line.\n");
    scanf("%[^\n]%*c", para);

    int len = strlen(para);
    // para[len] = 0; // gets rid of \n from fgets

    // 2
    wspPara(para, len);
    printf("%s\n\n", para);

    // 3
    upperPara(para, len);
    printf("%s\n\n", para);

    // 4
    mpInit();
    mapify(para, len);
    mpPrint();
    printf("\n");

    // 5
    mpSSsort();

    // 6
    mpPrint();
    printf("\n");

    // 7
    bool nfflag;
    while(true){
        nfflag = true;
        printf("Enter a word (0 to exit): ");
        char word[55];
        scanf("%[^\n]%*c", word);
        // word[strlen(word)-1] = 0;
        upperPara(word, strlen(word));
        if(strcmp(word, "0") == 0) break;
        int i;
        for(i = 0; i < mpct; i++){
            if(strcmp(mp[i].ff, word) == 0){
                printf("%d\n", mp[i].ss);
                nfflag = false;
                break;
            }
        }
        if(nfflag) printf("0\n");
    }

    return 0;
}

void mpInit(){
    int i;
    for(i = 0; i < 1010; i++){
        mp[i].ss = 0;
    }
}

void mpPrint(){
    int i;
    for(i = 0; i < mpct; i++){
        printf("%s %d\n", mp[i].ff, mp[i].ss);
    }
}

void wspPara(char para[], int len){
    int i;
    for(i = 0; i < len; i++){
        if(para[i] < 'A' || para[i] > 'z' || (para[i]>'Z' && para[i]<'a'))
            para[i] = ' ';
    }
}

void upperPara(char para[], int len){
    int i;
    for(i = 0; i < len; i++){
        if(para[i] >= 'a' && para[i] <= 'z') para[i] -= 32;
    }
}

void mapify(char para[], int len){
    char temp[55];
    int tempct = 0;
    int i;
    for(i = 0; i < len; i++){
        if(para[i] == ' ' && tempct){
            temp[tempct] = 0;
            int j;
            bool flag = true;
            for(j = 0; j < mpct; j++){
                if(strcmp(mp[j].ff, temp) == 0){
                    (mp[j].ss)++;
                    flag = false;
                    break;
                }
            }
            if(flag){
                strcpy(mp[mpct].ff, temp);
                (mp[mpct].ss)++;
                mpct++;
            }
            tempct = 0;
        }
        else if(para[i] == ' ') continue;
        else temp[tempct++] = para[i];
    }
    if(tempct){
        temp[tempct] = 0;
        int j;
        bool flag = true;
        for(j = 0; j < mpct; j++){
            if(strcmp(mp[j].ff, temp) == 0){
                (mp[j].ss)++;
                flag = false;
                break;
            }
        }
        if(flag){
            strcpy(mp[mpct].ff, temp);
            (mp[mpct].ss)++;
            mpct++;
        }
        tempct = 0;
    }
}

void mpSSsort(){
    int i, j;
    for(i = mpct-1; i >= 0; i--){
        for(j = 0; j < i; j++){
            if(mp[j].ss < mp[j+1].ss){
                pair temp = mp[j];
                mp[j] = mp[j+1];
                mp[j+1] = temp;
            }
        }
    }
}