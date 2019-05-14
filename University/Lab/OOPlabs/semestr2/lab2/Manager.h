#pragma once
#include "Employee.h"
#include <string>
#include <list>


class Manager : public Employee {
public:
    Manager();
    Manager(std::string f_name, std::string l_name, int age, int id);
    Manager(const Manager &manager);
    void Display() override;
    Person AddSubordinate(Person person);//Not using pointers, like in the case(segmentation fault, when using pointers)
    void DisplaySubordinates();
private:
    std::list<Person> subordinates;//Not using pointers, like in the case (segmentation fault, when using pointers)
};