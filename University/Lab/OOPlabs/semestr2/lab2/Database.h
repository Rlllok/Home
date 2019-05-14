#pragma once
#include <vector>
#include <string>
#include "Person.h"

class Database {
public:
    Database();
    bool LoadFromFile(const char* filename);
    void ArrangeSubordinates();
    Person HireEmployee(Person person);
    void DisplayDepartmentEmployees(std::string department);
    bool FireEmployee;
    void DisplayAll();
    std::vector<Person> SQL(const char* field, const char* cond, const char* value);
    void ShowRecordSet();
private:
    std::vector<Person> employees;
};