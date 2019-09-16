/************************************************************************       
 * file: Database.cpp                                                         
 * Database class realization                                                 
 * author: Novikov Alexander KV-72                                              
 * written: 27/04/2019                                                          
 * last modified: 06/05/2019                                                    
 ************************************************************************/
#include "Database.h"
#include "Employee.h"
#include "Manager.h"
#include "Person.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>

Database::Database() {
    employees.clear();
}


bool Database::LoadFromFile(const char* filename) {
    if (filename == NULL) return false;
    std::ifstream file;

    file.open(filename);

    std::vector<std::string> result;
    std::string temp, word, line;

    while (std::getline(file, line)) {
        result.clear();

        std::stringstream lineStream(line);

        while (std::getline(lineStream, word, ',')) {
            result.push_back(word);
        }

        if (std::stoi(result[0]) == 0) {
            Employee* employee = new Employee(result[2], result[3], std::stoi(result[4]), std::stoi(result[1]));
            employee->SetDepartment(result[5]);
            employee->SetSalary(std::stoi(result[6]));
            employees.push_back(employee);
        } else if (std::stoi(result[0]) == 1) {
            Manager* manager = new Manager(result[2], result[3], std::stoi(result[4]), std::stoi(result[1]));
            manager->SetDepartment(result[5]);
            manager->SetSalary(std::stoi(result[6]));
            employees.push_back(manager);
        } else {
            std::cout << "Wrong Type! " << result[2] << " " << result[3] << " is type " << result[0] << std::endl;
            return false;
        }
    }

    file.close();

    return true;
}


void Database::ArrangeSubordinates() {
    for (auto iter = employees.begin(); iter != employees.end(); iter++) {
        if ((*iter)->ReturnType() == 1) {
            for (auto iter2 = employees.begin(); iter2 != employees.end(); iter2++) {
                if ((*iter2)->ReturnType() == 0 && dynamic_cast<Manager*>(*iter)->GetDepartment() == dynamic_cast<Employee*>(*iter2)->GetDepartment()) {
                    dynamic_cast<Manager*>(*iter)->AddSubordinate(*iter2);
                }
            }
        }
    }
}


Person* Database::HireEmployee(Person* person) {
    if (person == NULL) return NULL;

    if (person->ReturnType() == 0) {
        Employee* employee = new Employee;
        employee = dynamic_cast<Employee*>(person);

        for (auto iter = employees.begin(); iter != employees.end(); iter++) {
            if (employee->GetId() == dynamic_cast<Employee*>(*iter)->GetId()) {
                std::cout << "Wrong ID! ID is repeated! Problem with ID number " 
                << employee->GetId() 
                << "! Cannot hire new employee." 
                << std::endl << std::endl;
                return NULL;
            }
        }
        employees.push_back(employee);
        ArrangeSubordinates();
        return employee;
    } else if (person->ReturnType() == 1) {
        Manager* manager = new Manager;
        manager = dynamic_cast<Manager*>(person);

        for (auto iter = employees.begin(); iter != employees.end(); iter++) {
            if (manager->GetId() == (dynamic_cast<Employee*>(*iter)->GetId())) {
                std::cout << "Wrong ID! ID is repeated! Problem with ID number " 
                << manager->GetId() 
                << "! Cannot hire new employee." 
                << std::endl << std::endl;
                return NULL;
            }
        }

        employees.push_back(manager);
        ArrangeSubordinates();
        return manager;
    }

    return NULL;
}


bool Database::FireEmployee(int id) {
    bool isDeleted = false;

    for (auto iter = employees.begin(); iter != employees.end(); iter++) {
        if (dynamic_cast<Employee*>(*iter)->GetId() == id) {
            employees.erase(iter);
            isDeleted = true;
            break;
        }
    }

    if (isDeleted) {
        for (auto iter = employees.begin(); iter != employees.end(); iter++) {
            if ((*iter)->ReturnType() == 1) {
                dynamic_cast<Manager*>(*iter)->CleanSubordinate();
            }
        }
        ArrangeSubordinates();
        return true;
    }

    return false;
}


void Database::DisplayDepartmentEmployees(std::string department) {
    std::cout << "Emloyees of " << department << "department:\n";
    for (auto iter = employees.begin(); iter != employees.end(); iter++) {
        if (dynamic_cast<Employee*>(*iter)->GetDepartment() == department) {
            (*iter)->Display();
            std::cout << std::endl;
        }
    }
}


std::vector<Person*> Database::SQL(const char* field, const char* cond, const char* value) {
    std::vector<Person*> personVector;

    if (strcmp(field, "age") == 0) {
        if (strcmp(cond, "le") == 0) {
            for (auto iter = employees.begin(); iter != employees.end(); iter++) {
                if ((*iter)->GetAge() <= std::atoi(value)) {
                    if ((*iter)->ReturnType() == 0) {
                        Employee* employee = new Employee;
                        *employee = *dynamic_cast<Employee*>(*iter);
                        personVector.push_back(employee);
                    }else if ((*iter)->ReturnType() == 1) {
                        Manager* manager = new Manager;
                        *manager = *dynamic_cast<Manager*>(*iter);
                        personVector.push_back(manager);
                    }
                }
            }
        } else if (strcmp(cond, "ge") == 0) {
                for (auto iter = employees.begin(); iter != employees.end(); iter++) {
                    if ((*iter)->GetAge() >= std::atoi(value)) {
                        if ((*iter)->ReturnType() == 0) {
                            Employee* employee = new Employee;
                            *employee = *dynamic_cast<Employee*>(*iter);
                            personVector.push_back(employee);
                        }else if ((*iter)->ReturnType() == 1) {
                            Manager* manager = new Manager;
                            *manager = *dynamic_cast<Manager*>(*iter);
                            personVector.push_back(manager);
                        }
                    }
                }
        } else {
            std::cout << "Wrong cond!" << std::endl;
        }
    } else if (strcmp(field, "salary") == 0) {
        if (strcmp(cond, "le") == 0) {
            for (auto iter = employees.begin(); iter != employees.end(); iter++) {
                if (dynamic_cast<Employee*>(*iter)->GetSalary() <= std::atoi(value)) {
                    if ((*iter)->ReturnType() == 0) {
                        Employee* employee = new Employee;
                        *employee = *dynamic_cast<Employee*>(*iter);
                         personVector.push_back(employee);
                    }else if ((*iter)->ReturnType() == 1) {
                        Manager* manager = new Manager;
                        *manager = *dynamic_cast<Manager*>(*iter);
                        personVector.push_back(manager);
                    }
                }
            }
        } else if (strcmp(cond, "ge") == 0) {
            for (auto iter = employees.begin(); iter != employees.end(); iter++) {
                if (dynamic_cast<Employee*>(*iter)->GetSalary() >= std::atoi(value)) {
                    if ((*iter)->ReturnType() == 0) {
                        Employee* employee = new Employee;
                        *employee = *dynamic_cast<Employee*>(*iter);
                         personVector.push_back(employee);
                    }else if ((*iter)->ReturnType() == 1) {
                        Manager* manager = new Manager;
                        *manager = *dynamic_cast<Manager*>(*iter);
                        personVector.push_back(manager);
                    }
                }
            }
        } else {
            std::cout << "Wrong cond!" << std::endl;
        }
    } else {
        std::cout << "Wrong field!" << std::endl;
    }

    return personVector;
}


void Database::ShowRecordSet(std::vector<Person*> personVector) {
    std::cout << "Record set: " << std::endl << std::endl;
    for (auto iter = personVector.begin(); iter != personVector.end(); iter++) {
        (*iter)->Display();
        std::cout << std::endl << std::endl;
    }
}


void Database::DisplayAll() {
    if (employees.empty()) {
        std::cout << "List of employees is empty" << std::endl;
    } else {
        for (auto iter = employees.begin(); iter != employees.end(); iter++) {
            std::cout << "Type:  " << (*iter)->ReturnType() << std::endl;
            (*iter)->Display();
            std::cout << std::endl << std::endl << std::endl;
        }
    }
}