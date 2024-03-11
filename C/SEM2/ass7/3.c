#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sToPoly(int *p, char *s){
    int flag = 0;
    int sign = 0;
    int coeff = 0;
    int exp = 0;
    for(int i = 0, j = 0; s[i] != 0; i++){
        if(s[i] == ' ')
            continue;
        if(s[i] == '+' || s[i] == '-'){
            if(!coeff){
                if(s[i] == '+')
                    sign = 0;
                else sign = 1;
                continue;
            }
            if(flag == 1 && exp == 0)
                exp = 1;
            if(sign)
                p[exp] -= coeff;
            else p[exp] += coeff;
            coeff = flag = exp = 0;
            if(s[i] == '+')
                sign = 0;
            else sign = 1;
        }
        else if(s[i] == 'x')
            flag = 1;
        else{
            if(!flag){
                coeff *= 10;
                coeff += s[i] - '0';
            }
            else{
                exp *= 10;
                exp += s[i] - '0';
            }
        }
    }
    if(!coeff);
    else if(flag == 1 && exp == 0)
        exp = 1;
    if(sign)
        p[exp] -= coeff;
    else p[exp] += coeff;
}

int main(){
    int p1[100], p2[100];
    char s1[1000], s2[1000];
    for(int i = 0; i < 100; i++) p1[i] = p2[i] = 0;
    printf("Enter polynomial 1 in x: ");
    scanf("%[^\n]%*c", s1);
    printf("Enter polynomial 2 in x: ");
    scanf("%[^\n]%*c", s2);
    sToPoly(p1, s1);
    sToPoly(p2, s2);
    for(int i = 0; i < 100; i++)
        p1[i] += p2[i];
    for(int i = 99; i >= 0; i--){
        if(!p1[i])
            continue;
        if(p1[i]<0){
            printf("%dx%d ", p1[i], i);
        }
        else printf("+%dx%d ", p1[i], i);
    }
}