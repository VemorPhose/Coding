#include <iostream>
using namespace std;

void compressString(string s, int l){
    int counter = 1;
    for(int i = 0; i < l-1; i++){
        // if(i == l - 1){
        //     if(counter == 1){
        //         snew += s[i];
        //     }
        //     else{
        //         snew += s[i];
        //         snew += (char)counter;
        //         counter = 1;
        //     }
        // }
        // else if(s[i + 1] == s[i]){
        //     counter++;
        // }
        // else{
        //     if(counter == 1){
        //         snew += s[i];
        //     }
        //     else{
        //         snew += s[i];
        //         snew += (char)counter;
        //         counter = 1;
        //     }
        // }
        if(s[i+1] == s[i]){
            counter++;
        }
        else if(s[i+1] != s[i]){
            if(counter != 1){
                cout << s[i] << counter;
                counter = 1;
            }
            else{
                cout << s[i];
            }
        }
    }
    if(s[l-1] != s[l-2]){
        cout << s[l-1];
    }
    cout << endl;
}

int t, l;
string s;
int main() {
	// your code goes here
	cin >> t;
	while(t--){
	    cin >> l;
	    cin >> s;
        compressString(s, l);
	}
	return 0;
}
