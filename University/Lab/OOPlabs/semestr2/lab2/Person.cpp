#include "Person.h"
#include <iostream>

Person::Person(){

}

Person::Person(std::string f_name, std::string l_name, int age) {
    this->f_name = f_name;
    this->l_name = l_name;
    this->age = age;
}

void Person::Display(){
    std::cout << "Name: " << this-> f_name << std::endl;
    std::cout << "Last name: " << this-> l_name << std::endl;
    std::cout << "Age: " << this-> age << std::endl;
}
