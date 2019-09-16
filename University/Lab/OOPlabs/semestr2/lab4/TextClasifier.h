/************************************************************************       
 * file: TextClasifier.cpp                                              
 * TextClasifier class declaration                                                
 * author: Novikov Alexander KV-72                                              
 * written: 03/06/2019                                                          
 * last modified: 04/06/2019                                                    
 ************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>


#define MAX_SCORE 150

#define LOWER_NGRAM_LEN	2
#define UPPER_NGRAM_LEN	5
#define CATEGORY_LEN 1000

typedef std::vector<std::pair<std::string, unsigned long>> frequency_map;

class TextClasifier {
public:
    TextClasifier() {category = "Unknown";}
    // ~TextClasifier();
    frequency_map getfreqs() {return this->freqs;}
    std::vector<std::string> ngram(std::string word);
    std::string getCategory() {return this->category;}
    void setCategory(std::string& categoty) {this->category = categoty;}
    void learn(std::istream& in);
    void dumpProfile(std::ostream& out);
    void learnFromDump(std::istream& in);
    long int score(const TextClasifier& textclasifier);
    void print() const;
private:
    frequency_map freqs;
    std::string category;
};