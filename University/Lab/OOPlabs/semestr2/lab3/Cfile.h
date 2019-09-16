/************************************************************************       
 * file: Cfile.h                                                         
 * Cfile class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 02/05/2019                                                          
 * last modified: 1/06/2019                                                    
 ************************************************************************/
#pragma once
#include <iostream>

class Cfile {
public:
    Cfile();
    Cfile(const char* filename,const char* creation_data,const int size);
    ~Cfile();

    friend std::ostream& operator << (std::ostream& out, const Cfile& cfile);
    char* getDate();
    bool operator== (const Cfile& cfile) const;

private:
    char* filename;
    char* creation_date;
    int size;
};