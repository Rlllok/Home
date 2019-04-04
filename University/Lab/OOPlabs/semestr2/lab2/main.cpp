#include "Person.h"
#include "Employee.h"

int main()
{
    Person person("Sasha", "Novikov", 19);
    person.Display();
    Employee employee("Biba", "boba", 104, 01);
    employee.Display();
    employee.SetDepartment("Dnepr");
    employee.SetId(2);
    employee.SetSalary(500);
    employee.Display();
    std::cout << employee.GetDepartment() << '\t' << employee.GetId() << std::endl;

    // operator= overloading test
    // Employee e;
    // e.Display();
    // e = employee;
    // e.Display();



    return 0;
}