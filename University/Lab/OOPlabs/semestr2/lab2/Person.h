/************************************************************************       
 * file: Person.h                                                         
 * Person class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#pragma once
#include <string>


class Person
{
public:
    Person();   
    Person(std::string f_name, std::string l_name, int age);
    virtual void Display();
    virtual int ReturnType() = 0;
    virtual int GetAge();
protected:
    std::string f_name;
    std::string l_name;
    int age;
};
