/************************************************************************       
 * file: Manager.cpp                                                         
 * Manager class realization                                                 
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#include "Manager.h"

Manager::Manager() {
    f_name.clear();
    l_name.clear();
    age = 0;
    id = 0;
    department.clear();
    salary = 0;
}


Manager::Manager(std::string f_name, std::string l_name, int age, int id) : Employee(f_name, l_name, age, id) {}


Manager::Manager(const Manager &manager) {
    *this = manager;
}


Person* Manager::AddSubordinate(Person *person) {
    if (person == NULL) return NULL;
    
    for (auto iter = subordinates.begin(); iter != subordinates.end(); iter++) {
        if (*(dynamic_cast<Employee*>(person)) == *(dynamic_cast<Employee*>(*iter)) 
        || (dynamic_cast<Employee*>(person))->GetId() == (dynamic_cast<Employee*>(*iter)->GetId())
        )
            return NULL;
    }

    subordinates.push_back(person);
    return person;
}


void Manager::CleanSubordinate() {
    subordinates.clear();
}


Manager& Manager::operator=(const Manager &manager) {
    this->f_name = manager.f_name;
    this->l_name = manager.l_name;
    this->age = manager.age;
    this->id = manager.id;
    this->salary = manager.salary;
    this->department = manager.department;
    this->subordinates = manager.subordinates;
    return *this;
}


void Manager::DisplaySubordinates() {
    std::cout << "Subordinates of " << f_name << " " << l_name << ":" << std::endl;
    if (subordinates.empty()) {
        std::cout << "None" << std::endl;
        return;
    }
    for (auto iter = subordinates.begin(); iter != subordinates.end(); iter++) {
        std::cout << "________________________________\n";
        (*iter)->Display();
        std::cout << "________________________________\n";
    }
}


void Manager::Display() {
    Employee::Display();
    DisplaySubordinates();
}


int Manager::GetAge() {
    return Person::GetAge();    
}


int Manager::GetSalary() {
    return Employee::GetSalary();
}


int Manager::ReturnType() {
    return 1;
}