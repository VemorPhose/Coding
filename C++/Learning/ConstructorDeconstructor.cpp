#include <iostream>

using namespace std;

class House {
private:
    std::string location;
    int rooms;

public:
    // Constructor with default parameters
    House(std::string loc = "New York", int num = 5) {
        location = loc;
        rooms = num;
    }
    
    // Destructor
    ~House() {
        std::cout << "Moved away from " << location << "\n";
  }
};

// NOTE: CONSTRUCTORS ONLY ASSIGN VALUE TO THE INITIALIZED VARIABLE. THEY DON'T INITIALIZE VARIABLES.
class Book {
private:
    const std::string title; // const variables cannot be assigned to once initialized.
    const int pages; // thus normal constructors don't work.
    // instead, a member initializer list is used.
public:
    Book() 
        : title("Diary"), pages(100) {} // Member initializer list
    void readBook(void){
        std::cout << title << ' ' << pages << std::endl;
    }
    ~Book(){
        std::cout << "Burnt " << title << std::endl;
    }
};

int main()
{
    // implicit declaration
    House default_house;	// Calls House("New York", 5)
    House texas_house("Texas");	// Calls House("Texas", 5)
    House big_florida_house("Florida", 10);	// Calls House("Florida", 10)

    // explicit declaration
    House explicit_house = House("Iowa", 15);
    
    Book Diary;
    Diary.readBook();

    // note: deconstructor kills variables from last declared to first declared.

    return 0;
}