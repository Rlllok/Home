#pragma once
#include "Person.h"
#include <string>
#include <iostream>

class Employee : public Person
{
public:
    Employee();
    Employee(std::string f_name, std::string l_name, int age, int id);
    Employee(const Employee&);
    Employee& operator=(const Employee&);
    void SetSalary(int salary);
    void SetDepartment(std::string department);
    void SetId(int id);
    int GetId();
    std::string GetDepartment();
    void Display() override;
protected:
    std::string department;
    int salary;
    int id;
};