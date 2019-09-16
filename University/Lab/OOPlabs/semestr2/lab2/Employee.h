/************************************************************************       
 * file: Employee.h                                                         
 * Employee class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#pragma once
#include "Person.h"
#include <string>
#include <iostream>


class Employee : public Person {
public:
    Employee();
    Employee(std::string f_name, std::string l_name, int age, int id);
    Employee(const Employee&);
    Employee& operator=(const Employee&);
    bool operator==(const Employee& employee);
    void SetSalary(int salary);
    void SetDepartment(std::string department);
    void SetId(int id);
    int GetId();
    std::string GetDepartment();
    void Display() override;
    int ReturnType() override;
    int GetAge() override;
    virtual int GetSalary();
protected:
    std::string department;
    int salary;
    int id;
};