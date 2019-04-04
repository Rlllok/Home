#pragma once
#include <string>


class Person
{
public:
    Person();   
    Person(std::string f_name, std::string l_name, int age);
    virtual void Display();
protected:
    std::string f_name;
    std::string l_name;
    int age;
};
