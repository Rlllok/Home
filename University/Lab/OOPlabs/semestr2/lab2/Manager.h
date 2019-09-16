/************************************************************************       
 * file: Manager.h                                                         
 * Manager class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#pragma once
#include "Employee.h"
#include <string>
#include <list>


class Manager : public Employee {
public:
    Manager();
    Manager(std::string f_name, std::string l_name, int age, int id);
    Manager(const Manager &manager);
    Manager& operator=(const Manager &manager);
    void Display() override;
    int ReturnType() override;
    int GetAge() override;
    int GetSalary() override;
    Person* AddSubordinate(Person *person);
    void CleanSubordinate();
    void DisplaySubordinates();
private:
    std::list<Person *> subordinates;
};