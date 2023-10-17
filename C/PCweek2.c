// Pratapaditya Chander 2301154
#include <stdio.h>
void main(){
    int t; scanf("%d", &t);
    while(t--){
        int startVal, target, minCount = 0; scanf("%d %d", &startVal, &target);
        while(startVal != target){
            if(target<startVal) target++;
            else if(target%2!=0) target += 1;
            else target/=2;
            minCount++;
        }
        printf("%d\n", minCount);
    }
}