/************************************************************************       
 * file: Cfile.h                                                         
 * Cfile class realization                                                
 * author: Novikov Alexander KV-72                                              
 * written: 02/05/2019                                                          
 * last modified: 1/06/2019                                                    
 ************************************************************************/
#include "Cfile.h"
#include "stdio.h"
#include "string.h"


Cfile::Cfile() {
    filename = new char[80];
    creation_date = new char[80];
    strcpy(filename, "str");
    strcpy(creation_date, "str");
    size = 0;
}


Cfile::~Cfile() {

}


Cfile::Cfile(const char* filename,const char* creation_date,const int size) {
    this->filename = new char[80];
    this->creation_date = new char[80];
    strcpy(this->filename, filename);
    strcpy(this->creation_date, creation_date);
    this->size = size;
}


char* Cfile::getDate() {
    return creation_date;
}


bool Cfile::operator==(const Cfile& cfile) const{
    if (strcmp(this->filename, cfile.filename) == 0) {
        if (strcmp(this->creation_date, cfile.creation_date) == 0) {
            if (this->size == cfile.size) {
                return true;
            }
        }
    }

    return false;
}


std::ostream& operator<< (std::ostream& out, const Cfile& cfile) {
    out << "Filename: " << cfile.filename << std::endl;
    out << "Creation data: " << cfile.creation_date << std::endl;
    out << "Size: " << cfile.size;

    return out;
}