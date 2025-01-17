#include <iostream>
#include <unordered_map>
#include <map>
using namespace std;
int main(){
    std::unordered_map<std::string, int> country_codes( 
    {{"India", 91}, 
    {"Italy", 39}, 
    {"Italy", 27}});
    // country_codes contains {"India", 91} and {"Italy", 39}.

    country_codes.insert({"Thailand", 66});
    country_codes.insert({"Peru", 51});
    country_codes.insert({"Peru", 9});  // Duplicate key is not inserted

    // inserting as in Python:
    country_codes["Thailand"] = 66;
    country_codes["Peru"] = 51;

    country_codes.erase("Thailand");
    // When .erase() is used this way, it returns 1 if an element was successfully erased, and 0 otherwise.

    // The .count() function searches in the hash map and returns the number of elements whose key matches the argument value.

    // Because hash maps do not allow for duplicate keys, the .count() function is a convenient way of checking 
    // whether the hash map contains an element with the specified key:
    country_codes["Argentina"] = 54;
    country_codes["Belgium"] = 32;

    if (country_codes.count("Belgium")) {
    std::cout << "There is a code for Belgium";
    }
    else {
    std::cout << "There isn't a code for Belgium";
    }

    country_codes["Japan"] = 81;
    country_codes["Turkey"] = 90;

    std::cout << country_codes["Japan"];     // Outputs: 81

    // [] operator will insert a new element into the hash map if the provided argument does not match 
    // the key of any element in the container. To avoid this behavior, use the .at() method instead of []. 
    // .at() will throw an out_of_range exception if there is no match:
    std::cout << country_codes.at("Pakistan");  // Error: out_of_range

    std::cout << country_codes.size();  // Outputs: 3

    std::cout << country_codes.empty();  // Outputs: 0

    country_codes.erase("Japan");
    country_codes.erase("Turkey");
    country_codes.erase("Pakistan");

    std::cout << country_codes.empty();   // Outputs: 1

    // iterating through hashmap:
    for(auto it: country_codes){
    std::cout << it.first << " " << it.second << "\n";
    }

    // unordered_map vs map:
    std::unordered_map<int, char> unordered({{2, 'b'}, {1, 'a'}, {3, 'c'}});
    for(auto it: unordered){
    std::cout << it.first << " " << it.second << "\n";
    }

    std::cout << "\n";

    std::map<int, char> ordered({{2, 'b'}, {1, 'a'}, {3, 'c'}});
    for(auto it: ordered){
    std::cout << it.first << " " << it.second << "\n";
    }
    
    return 0;
}