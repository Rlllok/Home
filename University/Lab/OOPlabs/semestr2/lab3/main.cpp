/************************************************************************       
 * file: main.cpp                                                         
 * author: Novikov Alexander KV-72                                              
 * written: 02/05/2019                                                          
 * last modified: 1/06/2019                                                    
 ************************************************************************/
#include "Iterator.h"
#include "List.h"
#include "Cfile.h"
#include "string.h"
#include <fstream>
#include <vector>
#include <sstream>


void loadFromFile(const char* filename, List<Cfile>& list);
std::string reverseDate(const char* date);
void deleteIfLess(const char* date, List<Cfile>& list, List<Cfile>& l);


int main() {
    List<int> list_int;

    std::cout << "List test: " << std::endl;
    list_int.push_front(1);
    list_int.push_front(2);
    list_int.push_front(3);
    list_int.push_front(4);
    list_int.push_front(5);
    list_int.print();
    std::cout << "SIZE: " << list_int.size() << std::endl;
    list_int.pop_front();
    list_int.print();
    std::cout << "SIZE after pop: " << list_int.size() << std::endl;
    // List<int>::iterator iter = list_int.begin();
    std::cout << "list after remove 3: " << std::endl;
    list_int.remove(3);
    list_int.print();
    List<int>::iterator iter = list_int.find(1);
    std::cout << "Find 1: " << (*iter).data << std::endl;

    list_int.clear();
    std::cout << "After clear: " << std::endl;
    list_int.print();


    List<Cfile> list;
    List<Cfile> deleted;
    Cfile cfile("Name", "date", 10);
    loadFromFile("input.csv", list);
    std::cout << "List: " << std::endl;
    list.print();
    std::cout << "Deleted: " << std::endl;
    deleted.print();
    std::cout << std::endl;
    deleteIfLess("10.04.2019", list, deleted);
    std::cout << "List after deleteIfless for date 10.04.2019: " << std::endl;
    list.print();
    std::cout << "Deleted after deleteIfless for date 10.04.2019: " << std::endl;
    deleted.print();
    return 0;
}

void loadFromFile(const char* filename, List<Cfile>& list) {
    if (filename == NULL) return;

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

        Cfile cfile(result[0].c_str(), result[1].c_str(), stoi(result[2]));
        list.push_front(cfile);   
    }
}


std::string reverseDate(const char* date) {
    std::vector<std::string> date_vector;
    std::string tmp = date;
    std::string word;

    std::stringstream tmpStream(tmp);

    while(std::getline(tmpStream, word, '.')){
        date_vector.push_back(word);
    }

    std::string revers_date = date_vector[2] + "." + date_vector[1] + "." + date_vector[0];

    return revers_date;
}


void deleteIfLess(const char* date, List<Cfile>& list, List<Cfile>& l) {
    List<Cfile>::iterator iter = list.begin();

    while(iter != list.end()) {
        if(strcmp(reverseDate(date).c_str(), reverseDate((*iter).data.getDate()).c_str()) > 0) {
            list.splice(iter, l);
            iter = list.begin();
        }
        iter++;
    }
}