#include <stack>
#include <queue>
#include <iostream>
using namespace std;
int main(){
    std::stack<int> plates;
    plates.push(10);
    plates.push(8);
    plates.push(5);

    plates.pop();

    std::cout << plates.top();  // Outputs: 8

    std::stack<int> tower;

    tower.push(3);
    tower.push(2);
    tower.push(1);

    std::cout << tower.size();  // Outputs: 3

    std::cout << tower.empty(); // Outputs: 0

    tower.pop();
    tower.pop();
    tower.pop();

    std::cout << tower.empty(); // Outputs: 1

    // -----------------------------------------------

    std::queue<std::string> line;
    line.push("Amy");
    line.push("Bella");
    line.push("Chloe");

    line.pop();

    std::cout << line.front();  // Outputs: Bella

    std::cout << line.back();   // Outputs: Chloe

    std::queue<int> order;

    order.push(10);
    order.push(9);
    order.push(8);

    std::cout << order.size();  // Outputs: 3

    std::cout << order.empty(); // Outputs: 0

    order.pop();
    order.pop();
    order.pop();

    std::cout << order.empty(); // Outputs: 1

    return 0;
}