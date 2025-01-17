#include <iostream>
#include <string>
using namespace std;

#define FOR(i, a, n) for(int i = a; i < n; i++)

const int MAX_NUMBER_OF_NODES = 20;  // Maximum number of nodes in the trie
const int ALPHABET_SIZE = 26;        // 'a' to 'z' corresponds to 26 letters

// Initialize trie with -1 indicating no connections
int x[MAX_NUMBER_OF_NODES][ALPHABET_SIZE], nex = 1; 
bool isEnd[MAX_NUMBER_OF_NODES];  // Marks the end of valid words

// Function to insert a string into the trie
void build(string s){
    int i = 0, v = 0;
    while(i < s.size()){
        int c = s[i] - 'a';  // Map character to 0-25 for 'a' to 'z'
        if(x[v][c] == -1)
            v = x[v][c] = nex++;  // Move to next node if it's a new character
        else
            v = x[v][c];  // Move to existing node if character already exists
        i++;
    }
    isEnd[v] = true;  // Mark the end of the word
}

// Recursive function to read and print all stored strings in the trie
void read(int v, string s){
    if(isEnd[v]) {
        cout << s << endl;  // Print the string when we reach the end of a valid word
    }

    // Traverse all possible connections for letters 'a' to 'z'
    FOR(i, 0, ALPHABET_SIZE){
        if(x[v][i] != -1){
            read(x[v][i], s + char(i + 'a'));  // Recursively traverse the trie
        }
    }
}

// Function to print the 2D array representing the trie
void printTrie() {
    FOR (i, 0, ALPHABET_SIZE) {
        FOR (j, 0, MAX_NUMBER_OF_NODES) {
            cout << x[j][i] << " ";  // Print the trie array
        }
        cout << endl;
    }
}

int main() {
    // Initialize all values in the trie to -1 (no connections)
    for(int i = 0; i < MAX_NUMBER_OF_NODES; i++) {
        for(int j = 0; j < ALPHABET_SIZE; j++) {
            x[i][j] = -1;
        }
        isEnd[i] = false;  // No word ends at any node initially
    }

    // Insert strings into the trie
    build("banana");
    build("cat");
    build("bandage");

    // Print the trie structure (2D array)
    printTrie();

    // Read and print all strings stored in the trie
    read(0, "");  // Start from the root node
    return 0;
}
