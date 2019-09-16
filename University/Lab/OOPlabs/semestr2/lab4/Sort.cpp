/************************************************************************       
 * file: Sort.cpp                                              
 * Sort functions realization                                                
 * author: Novikov Alexander KV-72                                              
 * written: 03/06/2019                                                          
 * last modified: 04/06/2019                                                    
 ************************************************************************/
#include "Sort.h"


bool descending_sort(std::pair<std::string, unsigned long> elem1, std::pair<std::string, unsigned long> elem2) {
    return elem1.second > elem2.second;
}