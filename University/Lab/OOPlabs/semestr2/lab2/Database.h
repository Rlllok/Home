/************************************************************************       
 * file: Database.h                                                         
 * Database class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#pragma once
#include <vector>
#include <string>
#include "Person.h"

class Database {
public:
    Database();
    bool LoadFromFile(const char* filename);
    void ArrangeSubordinates();
    Person* HireEmployee(Person* person);
    void DisplayDepartmentEmployees(std::string department);
    bool FireEmployee(int id);
    void DisplayAll();
    std::vector<Person*> SQL(const char* field, const char* cond, const char* value);
    void ShowRecordSet(std::vector<Person*>);
private:
    std::vector<Person*> employees;
};