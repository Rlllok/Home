#include "Manager.h"

Manager::Manager() {}


Manager::Manager(std::string f_name, std::string l_name, int age, int id) : Employee(f_name, l_name, age, id) {}


Person Manager::AddSubordinate(Person person) {
    subordinates.push_back(person);
    return person;
}


void Manager::DisplaySubordinates() {
    for (auto iter = subordinates.begin(); iter != subordinates.end(); iter++) {
        iter->Display();
    }
}


void Manager::Display() {
    Employee::Display();
}