#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
    int a, b, c;

public:
    int d, e;

    void setData(int a1, int b1, int c1); // Declaration

    void getData()
    {
        cout << "The value of a is " << a << endl;
        cout << "The value of b is " << b << endl;
        cout << "The value of c is " << c << endl;
        cout << "The value of d is " << d << endl;
        cout << "The value of e is " << e << endl;
    }
};

void Employee ::setData(int a1, int b1, int c1) // Definition
{
    a = a1;
    b = b1;
    c = c1;
}

class Binary
{
    string s; // note: by default all members of class are private.

public:
    void read(void);
    void chk_bin(void);
    void ones(void);
    void display(void);
};

void Binary ::read(void)
{
    cout << "Enter a binary number" << endl;
    cin >> s;
}

void Binary ::chk_bin(void)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s.at(i) != '0' && s.at(i) != '1')
        {
            cout << "not a binary" << endl;
            exit(0);
        }
    }
}

void Binary ::ones(void)
{
    chk_bin(); // nesting of member function.
    // if chk_bin() function made private, external call as in main() would not work, and only functions defined within the class
    // can access chk_bin(), such as this.
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0')
            s[i] = '1';
        else if (s[i] == '1')
            s[i] = '0';
    }
}

void Binary ::display(void)
{
    for (int i = 0; i < s.length(); i++)
    {
        cout << s[i];
    }
    cout << endl;
}

int main()
{
    Employee ram;
    // ram.a = 5 ---> gives error, ram.a is inaccessible as private.
    ram.d = 5;
    ram.e = 6;            // public attributes accessible from outside.
    ram.setData(1, 2, 4); // private attributes accessible only by functions defined within the class.
    ram.getData();

    // nesting of member functions.
    Binary b;
    b.read();
    b.chk_bin();
    b.display();
    b.ones();
    b.display();

    return 0;
}