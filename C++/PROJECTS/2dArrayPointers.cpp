#include <iostream>
using namespace std;
int main(){
    int cols, rows, in;
    cin >> cols >> rows;
    int * arr = new int[cols * rows];

    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            cin >> in;
            *(arr + i * cols + j) = in;
        }
    }

    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            cout << *(arr + i * cols + j) << ' ';
        }
        cout << endl;
    }

    delete[] arr;
    return 0;
}