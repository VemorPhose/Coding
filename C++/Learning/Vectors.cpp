#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
    std::vector<int> weights;
    weights.push_back(25);
    weights.push_back(45);

    // weights contains {25, 45}

    weight.pop_back();
    // weights contains {25}

    std::vector<char> alphabet = {'a', 'b', 'c'};
    std::cout << alphabet[2];  // Output: c

    std::cout << alphabet.front();  // Output: a

    std::cout << alphabet.back();   // Output: c

    std::vector<std::string> colors = {"Red", "Green", "Blue"}
    std::cout << colors.size(); // Outputs: 3

    std::cout << colors.empty();    // Outputs: 0

    colors.pop_back();
    colors.pop_back();
    colors.pop_back();

    std::cout << colors.empty();    // Outputs: 1

    std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    for (int i = 0; i < vowels.size(); i++) {
    std::cout << vowels[i] << " ";
    }
    // Outputs: a e i o u

    for (char letter: vowels) {
    std::cout << letter << " ";
    }
    // Outputs: a e i o u

    std::vector<int> a={1,2,3};
    a.erase(std::find(a.begin(),a.end(),2)); // .erase() method for vectors takes an index argument.
    // find method works for arrays, vectors as well as strings, with the same format of arguments.
    // count method is also similar to find method.

    return 0;
}