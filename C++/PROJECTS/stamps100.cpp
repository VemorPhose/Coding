#include <iostream>
using namespace std;
int t, n;
int main() {
	// your code goes here
	cin >> t;
	while(t--){
	    string s, ns = "";
	    int flag = 1, counter = n;
	    cin >> n;
	    cin >> s;
	    for(int i = 0; i < n; i++){
	        if(s[i] == '1'){
	            counter = i;
	            break;
	        }
	    }
	    if(counter<(n-2)){
	        for(int i = 0; i < counter; i++){
	            ns += '0';
	        }
	        ns += '1';
	        for(int i = 0; i < (n - counter - 1); i++){
	            ns += '0';
	        }
	        cout << ns << '\n';
	    }
	    else cout << s << '\n';
	    
	}
	return 0;
}
