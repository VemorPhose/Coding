#include <unordered_set>
#include <set>
#include <iostream>
using namespace std;
int main(){
    std::unordered_set<int> primes({2, 3, 5, 5});    // primes contains {2, 3, 5}

    primes.insert(7);
    primes.insert(7);  // Duplicate value is not inserted

    primes.erase(7);
    // When .erase() is used this way, it returns 1 if an element was successfully erased, and 0 otherwise.

    // The .count() function searches in the set and returns the number of elements that match the argument value.
    // Because sets do not allow for duplicate keys, the .count() function is a convenient way of checking 
    // whether the set contains a specified element:
    if (primes.count(4)) {
        std::cout << "4 is a prime";
    }
    else {
        std::cout << "4 is not a prime";
    }

    std::unordered_set<char> symbols({'x', 'y', 'z'});
    std::cout << symbols.size();    // Outputs: 3

    std::cout << symbols.empty();  // Outputs: 0

    symbols.erase('x');
    symbols.erase('y');
    symbols.erase('z');

    std::cout << symbols.empty();   // Outputs: 1

    // As the name suggests, an unordered_set stores elements in no particular order. 
    // Searching, inserting, and deleting an element from an unordered_set is generally faster compared to a set.

    // On the other hand, a set stores elements following a specific order and 
    // can be iterated directly based on the order of its elements.

    // To demonstrate the difference, the following example iterates through 
    // a unordered_set and a set containing the same elements:
    std::unordered_set<int> unordered({4, 2, 7, 1, 3});
    std::cout << "unordered_set: ";
    for(int n: unordered) {
    std::cout << n << " ";
    }

    std::cout << "\n";

    std::set<int> ordered({4, 2, 7, 1, 3});
    std::cout << "set: ";
    for(int n: ordered) {
    std::cout << n << " ";
    }
    // NOTE: unordered_set is most of the time faster. Use it over set.

    return 0;
}