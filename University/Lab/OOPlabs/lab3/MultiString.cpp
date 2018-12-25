#include "MultiString.h"

MultiString::MultiString(){
    str_nmb = 1;
    buf = new char*[str_nmb];
    for(int i = 0; i < str_nmb; i++){
        buf[i] = new char;
        buf[i] = NULL;
    }
    buf[0][0] = '9';
    std::cout << buf[0][0] << std::endl;
}

MultiString::~MultiString(){
    if (str_nmb)
        delete [] buf[0];
    delete [] buf;
}
