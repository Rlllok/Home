#include "Person.h"
#include "Employee.h"
#include "Manager.h"
#include "Database.h"
#include <iostream>

#include <vector>

int main() {
    // Person person("Biba", "Boba", 30);
    // person.Display();
    // Person person1("Biba1", "Boba1", 30);
    // Person person2("Biba2", "Boba2", 30);

    // Employee employee;
    // employee.Display();

    // Manager manager("Name", "L_name", 10, 1);
    // manager.SetDepartment("Dnepr");
    // // manager.Display();
    // manager.AddSubordinate(person);
    // manager.AddSubordinate(person1);
    // manager.AddSubordinate(person2);
    // manager.DisplaySubordinates();

    // operator= overloading test
    // Employee e;
    // e.Display();
    // e = employee;
    // e.Display();

    std::vector<Person*> vp;
    Manager manager;
    vp.push_back(&manager);
    vp[0]->Display();
    
    // Database database;
    // const char filename[] = "employees.csv";
    // database.LoadFromFile(filename);

    return 0;
}