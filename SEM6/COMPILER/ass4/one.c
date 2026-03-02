#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;
char prod[20][20];
char first[20][20];
char follow[20][20];
char res[20];

void addToRes(char c) {
    int i;
    for(i = 0; res[i] != '\0'; i++)
        if(res[i] == c) return;
    res[i] = c;
    res[i+1] = '\0';
}

void computeFirst(char c) {
    if(!isupper(c)) {
        addToRes(c);
        return;
    }
    for(int i = 0; i < n; i++) {
        if(prod[i][0] == c) {
            if(prod[i][2] == '#') {
                addToRes('#');
            } else {
                int j = 2;
                while(prod[i][j] != '\0') {
                    int foundEpsilon = 0;
                    computeFirst(prod[i][j]);
                    for(int k = 0; res[k] != '\0'; k++)
                        if(res[k] == '#') foundEpsilon = 1;
                    if(!foundEpsilon) break;
                    j++;
                }
            }
        }
    }
}

void computeFollow(char c) {
    if(prod[0][0] == c) addToRes('$');
    for(int i = 0; i < n; i++) {
        for(int j = 2; prod[i][j] != '\0'; j++) {
            if(prod[i][j] == c) {
                if(prod[i][j+1] != '\0') {
                    char tempRes[20]; strcpy(tempRes, res);
                    memset(res, 0, 20);
                    computeFirst(prod[i][j+1]);
                    for(int k = 0; res[k] != '\0'; k++) {
                        if(res[k] != '#') {
                             int l;
                             for(l=0; tempRes[l]!='\0'; l++) if(tempRes[l]==res[k]) break;
                             if(tempRes[l]=='\0') { tempRes[l]=res[k]; tempRes[l+1]='\0'; }
                        }
                    }
                    int hasEps = 0;
                    for(int k=0; res[k]!='\0'; k++) if(res[k]=='#') hasEps=1;
                    strcpy(res, tempRes);
                    if(hasEps) computeFollow(prod[i][0]);
                } 
                else if(prod[i][0] != c) {
                    computeFollow(prod[i][0]);
                }
            }
        }
    }
}

int main() {
    int i;
    char c;
    
    printf("Enter Number of Productions: ");
    scanf("%d", &n);
    printf("Enter Productions (e.g. S=A). Use '#' for epsilon:\n");
    for(i = 0; i < n; i++) scanf("%s", prod[i]);

    printf("\n--- FIRST SETS ---\n");
    for(i = 0; i < n; i++) {
        c = prod[i][0];
        int seen=0; 
        for(int k=0; k<i; k++) if(prod[k][0]==c) seen=1;
        if(seen) continue;
        
        memset(res, 0, 20);
        computeFirst(c);
        printf("First(%c) = { %s }\n", c, res);
    }

    printf("\n--- FOLLOW SETS ---\n");
    char done[20]; int d_ptr=0;
    for(i = 0; i < n; i++) {
        c = prod[i][0];
        int seen=0; 
        for(int k=0; k<d_ptr; k++) if(done[k]==c) seen=1;
        if(seen) continue;
        done[d_ptr++] = c;
        
        memset(res, 0, 20);
        computeFollow(c);
        printf("Follow(%c) = { %s }\n", c, res);
    }

    printf("\n--- PARSING ---\n");
    char input[100], stack[100];
    int top = 0, ip = 0;
    
    printf("Enter Input String (append $): ");
    scanf("%s", input);
    
    int len = strlen(input);
    if(input[len-1] != '$') {
        input[len] = '$';
        input[len+1] = '\0';
    }

    memset(stack, 0, 100); 
    stack[top] = '$';
    stack[++top] = prod[0][0]; 
    stack[top+1] = '\0'; 

    printf("\n%-20s %-20s %s\n", "Stack", "Input", "Action");
    printf("%-20s %-20s %s\n", "-----", "-----", "------");

    while(1) {
        printf("%-20s %-20s ", stack, input + ip);
        
        if(stack[top] == '$' && input[ip] == '$') {
            printf("ACCEPTED\n");
            break;
        }
        else if(stack[top] == input[ip]) {
            printf("Match %c\n", input[ip]);
            top--; 
            stack[top+1] = '\0';
            ip++;
        }
        else if(!isupper(stack[top])) {
            printf("ERROR (Terminal Mismatch: Expected '%c', found '%c')\n", stack[top], input[ip]);
            break;
        }
        else {
            int found = -1;
            for(int k = 0; k < n; k++) {
                if(prod[k][0] == stack[top]) {
                    memset(res, 0, 20);
                    computeFirst(prod[k][2]); 
                    
                    int inFirst = 0;
                    for(int z=0; res[z]!='\0'; z++) if(res[z] == input[ip]) inFirst=1;
                    
                    if(inFirst) { found = k; break; }
                    
                    for(int z=0; res[z]!='\0'; z++) {
                         if(res[z] == '#') {
                             char tempFollow[20];
                             char lhs = prod[k][0];
                             memset(res,0,20); 
                             computeFollow(lhs);
                             for(int y=0; res[y]!='\0'; y++) if(res[y]==input[ip]) found=k;
                         }
                    }
                    if(found != -1) break;
                }
            }
            
            if(found != -1) {
                printf("Expand %s\n", prod[found]);
                top--;
                stack[top+1] = '\0';
                
                for(int k = strlen(prod[found])-1; k >= 2; k--) {
                    if(prod[found][k] != '#') {
                        stack[++top] = prod[found][k];
                    }
                }
                stack[top+1] = '\0';
            } else {
                printf("ERROR (No Rule for [%c, %c])\n", stack[top], input[ip]);
                break;
            }
        }
    }
    return 0;
}