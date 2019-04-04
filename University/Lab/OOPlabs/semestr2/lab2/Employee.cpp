#include "Employee.h"

Employee::Employee()
{
    f_name.clear();
    l_name.clear();
    age = 0;
    id = 0;
    department.clear();
    salary = 0;
}

Employee::Employee(std::string f_name, std::string l_name, int age, int id) : Person(f_name, l_name, age)
{
    this->id = id;
    department.clear();
    salary = 0;
}

Employee::Employee(const Employee& employee)
{
    this->f_name = employee.f_name;
    this->l_name = employee.l_name;
    this->age = employee.age;
    this->id = employee.id;
}

Employee& Employee::operator=(const Employee& employee)
{
    this->f_name = employee.f_name;
    this->l_name = employee.l_name;
    this->age = employee.age;
    this->id = employee.id;
    return *this;
}

void Employee::SetSalary(int salary)
{
    this->salary = salary;
}

void Employee::SetDepartment(std::string department)
{
    this->department = department;
}

void Employee::SetId(int id)
{
    this->id = id;
}

int Employee::GetId()
{
    return this->id;
}

std::string Employee::GetDepartment()
{
    return this->department;
}

void Employee::Display()
{
    Person::Display();
    std::cout << "ID: " << id << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Salary: " << salary << std::endl;
}