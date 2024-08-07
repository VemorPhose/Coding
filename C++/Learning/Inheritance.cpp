#include <iostream>

// Basic Inheritance

// Base class
class Animal {
private:
    std::string gender;
    int age;

public: // constructor in base class.
    Animal(std::string new_gender, int new_age)
        : gender(new_gender), age(new_age) {}
};

// Derived class (Child Class) : declared by placing ":" after className. 
// After that, write access specifier (public) and Base Class.
class Dog: public Animal  {
private:
    std::string breed;

public:
    // Call base class constructor
    Dog(std::string new_gender, int new_age, std::string new_breed)
        : Animal(new_gender, new_age), breed(new_breed) {} // defining new constructor by inheriting constructor from base class.

    void sound() {
        std::cout << "Woof\n";
  }
};

// Multilevel Inheritance

class A {   // A is the base class
public:
    int a;

    A() { std::cout << "Constructing A\n"; }
};

class B: public A { // class B inherits from class A
public:
    int b;

    B() { std::cout << "Constructing B\n"; }
};

class C: public B { // class C inherits from class B
public:
    int c;

    C() { std::cout << "Constructing C\n"; }
};

int main() {
    // Calls Dog(string, int, string) constructor
    Dog buddy("male", 8, "Husky");
    
    // Output: Woof
    buddy.sound();

    // note: In an inheritance class, the MOST BASE CLASS IS ALWAYS CONSTRUCTED FIRST.
    C example;

    return 0;
}


