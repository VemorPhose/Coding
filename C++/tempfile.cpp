#include <iostream>
using namespace std;
int solution(int x, int y){
    if(x==y || x == 0 || y == 0) return x+y;
    else if(x > y){
        if((x-1)/y > 1){
            return solution(x-(x/y)*y, y);
        }
        else return solution(x-y, y);
    }
    else{
        if((y-1)/x > 1){
            return solution(x, y - (y/x)*x);
        }
        else return solution(x, y-x);
    }
}
int main() {
	// your code goes here
	int t, x, y;
	cin >> t;
	while(t--){
	    cin >> x >> y;
	    cout << solution(x, y) << endl;
	}
	return 0;
}
