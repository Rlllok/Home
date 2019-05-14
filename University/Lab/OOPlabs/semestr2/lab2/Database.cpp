#include "Database.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

Database::Database() {
    employees.clear();
}


bool Database::LoadFromFile(const char* filename) {
    std::ifstream file;

    file.open(filename);

    std::vector<std::string> result;
    std::string temp, word, line;

    while (std::getline(file, line)) {
        result.clear();
        // std::getline(file, line);

        std::stringstream lineStream(line);

        while (std::getline(lineStream, word, ',')) {
            result.push_back(word);
        }

        if (std::stoi(result[0]) == 0) {
            std::cout << "Type: " << "employee " << result[0] << std::endl;
        } else {
            std::cout << "Type: " << "manager "  << result[0] << std::endl;
        }
        std::cout << "Id: "             << result[1] << std::endl;
        std::cout << "First Name: "     << result[2] << std::endl;
        std::cout << "Last Name: "      << result[3] <<  std::endl;
        std::cout << "Age: "            << result[4] << std::endl;
        std::cout << "Dep: "            << result[5] << std::endl;
        std::cout << "Selary: "         << result[6] << std::endl;
        std::cout << "Subordinates: "   << "None" << std::endl;
        std::cout << std::endl;
    }

    file.close();

    return true;
}