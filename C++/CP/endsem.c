#include <stdio.h>

int lenstr(char s1[]){
    int i = 0;
    while(s1[i] != 0) i++;
    return i;
}

int sumNum(char *s){
    int n = lenstr(s);
    int sum = 0;
    int i;
    for(i = 0; i < n; i++){
        if(s[i]>='0' && s[i]<='9') sum += (int)(s[i] - '0');
    }
    return sum;
}

int main(){
    char s[201];
    printf("Enter a string: ");
    scanf("%[^\n]%*c", s);
    printf("\nEntered String: %s\n\n", s);


    int n = lenstr(s);
    int charflag[26];
    int i;
    for(i = 0; i < 26; i++) charflag[i] = 1;
    for(i = 0; i < n; i++){
        if(s[i]>='A' && s[i]<='Z'){
            charflag[s[i]-'A'] = 0;
        }
        else if(s[i]>='a' && s[i]<='z'){
            charflag[s[i]-'a'] = 0;
        }
    }
    int flag = 1;
    for(i = 0; i < 26; i++){
        if(charflag[i] != 0){
            flag = 0;
            break;
        }
    }
    if(flag==1) printf("Entered string contains all alphabets in English.\n\n");
    else printf("Entered string does not contain all alphabets in English.\n\n");


    printf("Sum of digits: ");
    char temps[201];
    int tempsInd = 0;
    char sEven[201];
    for(i = 0; i < n; i++){
        if(tempsInd != 0 && s[i] == ' '){
            temps[tempsInd] = 0;
            int sum = sumNum(temps);
            printf("%s=%d ", temps, sum);
            if(sum%2==0){
                temps[tempsInd] = ' ';
                temps[tempsInd+1] = 0;
                catstr(sEven, temps);
            }
            tempsInd = 0;
        }
        else if((s[i]>='A' && s[i]<='Z')||(s[i]>='a' && s[i]<='z')||(s[i]>='0' && s[i]<='9')) temps[tempsInd++] = s[i];
        if(i == (n-1) && tempsInd != 0){
            temps[tempsInd] = 0;
            int sum = sumNum(temps);
            printf("%s=%d ", temps, sum);
            if(sum%2==0){
                temps[tempsInd] = ' ';
                temps[tempsInd+1] = 0;
                catstr(sEven, temps);
            }
            tempsInd = 0;
        }
    }
    printf("\n\n");


    printf("String after removing words with odd sum: %s\n\n", sEven);


    return 0;
}