#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sToPoly(int *p, char *s){
    int flag = 0; // if 0, write to coeff, else write to exp
    int sign = 0; // 0 --> +, 1 --> -
    int coeff = 0;
    int exp = 0;
    // loop through each char of inputted string
    for(int i = 0, j = 0; s[i] != 0; i++){
        if(s[i] == ' ')
            continue; // skip whitespaces
        if(s[i] == '+' || s[i] == '-'){ // on encountering signs, means last elements is finito
            if(!coeff){ // if coefficient is zero, no need to update array
                if(s[i] == '+')
                    sign = 0; // updates sign for next element
                else sign = 1;
                continue; 
            }
            if(flag == 1 && exp == 0) // eg. 4x
                exp = 1;
            if(sign) // if sign is -, subtract coefficient from that index of array
                p[exp] -= coeff;
            else p[exp] += coeff;
            coeff = flag = exp = 0; // reset all variables for next element
            if(s[i] == '+')
                sign = 0; // updates sign for next element
            else sign = 1;
        }
        else if(s[i] == 'x')
            flag = 1; // switches write mode from coeff to exp on encountering 'x'
        else{
            if(!flag){ // updates coeff
                coeff *= 10;
                coeff += s[i] - '0';
            }
            else{ // updates exp
                exp *= 10;
                exp += s[i] - '0';
            }
        }
    }
    // for the last element to be inserted into array
    if(!coeff); // if coefficient is zero, no need to update array
    else if(flag == 1 && exp == 0) // eg. 4x
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