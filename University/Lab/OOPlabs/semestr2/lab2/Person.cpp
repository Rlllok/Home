/************************************************************************       
 * file: Person.cpp                                                         
 * Person class realization                                                 
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#include "Person.h"
#include <iostream>

Person::Person() {
    this->f_name.clear();
    this->l_name.clear();
    this->age = 0;
}


Person::Person(std::string f_name, std::string l_name, int age) : f_name(f_name), l_name(l_name), age(age) {
}


void Person::Display() {
    std::cout << "Name: " << this-> f_name << std::endl;
    std::cout << "Last name: " << this-> l_name << std::endl;
    std::cout << "Age: " << this-> age << std::endl;
}


int Person::GetAge() {
    return this->age;
}
