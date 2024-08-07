#include <iostream>
using namespace std;

class Employee
{
    int id;
    int salary;

public:
    void setId(void)
    {
        cout << "enter the id of employee" << endl;
        cin >> id;
    }

    void getId(void)
    {
        cout << "id of employee is " << id << endl;
    }
};

int main()
{
    Employee employees[4];
    for (int i = 0; i < 4; i++)
    {
        employees[i].setId();
        employees[i].getId();
    }
    return 0;
}