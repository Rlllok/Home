/************************************************************************       
 * file: Main.cpp                                                                                                          
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 30/05/2019                                                    
 ************************************************************************/
#include "Person.h"
#include "Employee.h"
#include "Manager.h"
#include "Database.h"
#include <iostream>

#include <vector>

int main() {
    Database database;
    const char filename[] = "employees.csv";
    database.LoadFromFile(filename);
    std::cout << std::endl;

    database.ArrangeSubordinates();
    database.DisplayAll();
    database.FireEmployee(0);
    std::cout << "ID 0 was deleted\n\n";
    database.DisplayAll();

    Employee* employee = new Employee("Jon", "Miller", 43, 10);
    std::cout << "Add new employee Jon Miller\n\n";
    database.DisplayAll();
    
    std::cout << "Show employees with salary equal or less than 190:\n";
    database.ShowRecordSet(database.SQL("salary", "le", "190"));

    std::cout << "Show employees with age ge than 30:\n";
    database.ShowRecordSet(database.SQL("age", "ge", "30"));

    return 0;
}