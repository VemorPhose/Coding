// Pratapaditya Chander 2301154
#include <stdio.h>
int solution(int startVal, int target){
    if(target <= startVal) return startVal - target;
    else if(target%2==1) return 1 + solution(startVal, target + 1);
    else return 1 + solution(startVal, target/2);
}
void main(){
    int t; scanf("%d", &t);
    while(t--){
        int startVal, target/*, minCount = 0*/; scanf("%d %d", &startVal, &target);
        // while(startVal != target){
        //     if(target<startVal) target++;
        //     else if(target%2!=0) target += 1;
        //     else target/=2;
        //     minCount++;
        // }
        printf("%d\n", solution(startVal, target));
    }
}