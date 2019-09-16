/************************************************************************       
 * file: Employee.cpp                                                         
 * Employee class realization                                                 
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#include "Employee.h"

Employee::Employee() {
    f_name.clear();
    l_name.clear();
    age = 0;
    id = 0;
    department.clear();
    salary = 0;
}


Employee::Employee(std::string f_name, std::string l_name, int age, int id) : Person(f_name, l_name, age), id(id), salary(0) {
    department.clear();
}


Employee::Employee(const Employee& employee) {
    *this = employee;
}


Employee& Employee::operator=(const Employee& employee) {
    this->f_name = employee.f_name;
    this->l_name = employee.l_name;
    this->age = employee.age;
    this->id = employee.id;
    this->department = employee.department;
    this->salary = employee.salary;
    return *this;
}


bool Employee::operator==(const Employee& employee) {
    if (
            this->f_name == employee.f_name
        and this->l_name == employee.l_name
        and this->age == employee.age
        and this->id == employee.id
        and this->department == employee.department
        and this->salary == employee.salary
    )
        return true;
    else
        return false;
}


void Employee::SetSalary(int salary) {
    this->salary = salary;
}


void Employee::SetDepartment(std::string department) {
    this->department = department;
}


void Employee::SetId(int id) {
    this->id = id;
}


int Employee::GetId() {
    return this->id;
}


std::string Employee::GetDepartment() {
    return this->department;
}


void Employee::Display() {
    Person::Display();
    std::cout << "ID: " << id << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Salary: " << salary << std::endl;
}


int Employee::GetAge() {
    return Person::GetAge();    
}


int Employee::GetSalary() {
    return this->salary;
}


int Employee::ReturnType() {
    return 0;
}