/************************************************************************       
 * file: TextClasifier.cpp                                              
 * TextClasifier class realization                                                
 * author: Novikov Alexander KV-72                                              
 * written: 03/06/2019                                                          
 * last modified: 04/06/2019                                                    
 ************************************************************************/
#include "TextClasifier.h"

#include <vector>
#include <string>
#include "Sort.h"


std::vector<std::string> TextClasifier::ngram(std::string word) {
    std::vector<std::string> ngram_value;
    std::string tmp_string;

    for (int ngram_length = LOWER_NGRAM_LEN; ngram_length <= UPPER_NGRAM_LEN; ngram_length++) {
		for (int i = 0; i < word.length(); i++) {
			if (!i) {
				tmp_string = "_" + word.substr(0, ngram_length - 1);
				while (tmp_string.length() < ngram_length) {
						tmp_string += "_";
				}
				ngram_value.push_back(tmp_string);
			}
			tmp_string = word.substr(i, ngram_length);
			while (tmp_string.length() < ngram_length) {
					tmp_string += "_";
			}
			ngram_value.push_back(tmp_string);
		}
	}
	return ngram_value;
}


void TextClasifier::learn(std::istream& in) {
    std::vector<char> separator_symbols = {
        ',', '.', ':', ';', '!', '?', '/', '\\', '|',
        '\n', '\t', '+', '-', '=', '(', ')', '[', ']', 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '\"' 
        };

    std::string buff_string;
    std::vector<std::string> ngrams;
    std::map<std::string, unsigned long> ngrams_map;
    std::map<std::string, unsigned long>::iterator iter_map;

    while (in >> buff_string) {
        //delete separators
        for (auto iter = separator_symbols.begin(); iter != separator_symbols.end(); iter++) {
            if (buff_string.find(*iter) != std::string::npos)
                buff_string.erase(buff_string.find(*iter), 1);
        }

        if (!buff_string.empty()) {
            ngrams = this->ngram(buff_string);

            for (auto iter = ngrams.begin(); iter != ngrams.end(); iter++) {
                if (ngrams_map.size() >= CATEGORY_LEN) {
                    iter_map = ngrams_map.find(*iter);
                    if (iter_map != ngrams_map.end()) {
                        ngrams_map[*iter]++;
                    }
                } else {
                    ngrams_map[*iter]++;
                }
            }
        }
    }

    for (auto iter = ngrams_map.begin(); iter != ngrams_map.end(); iter++) {
        freqs.push_back(*iter);
    }
    sort(freqs.begin(), freqs.end(), descending_sort);
}


void TextClasifier::dumpProfile(std::ostream& out) {
    out << "Dump for " << this->category << std::endl;
    for (int i = 0; i < freqs.size(); i++) {
        out << freqs[i].first << " " << freqs[i].second << std::endl;
    }
}


void TextClasifier::learnFromDump(std::istream& in) {
    std::string ngram_value;
    unsigned long ngram_count;
    char buff[128];
    std::pair<std::string, unsigned long> ngram_tmp;

    in.getline(buff, 128);

    while (in >> ngram_value && in >> ngram_count) {
        ngram_tmp.first = ngram_value;
        ngram_tmp.second = ngram_count;
        freqs.push_back(ngram_tmp);
    }   
}


long int TextClasifier::score(const TextClasifier& textclasifier) {
    int score_value = 0;
	bool matches_is_founded = false;
    
	for (int i = 0; i < this->freqs.size(); i++) {
		matches_is_founded = false;

		for (int j = 0; j < textclasifier.freqs.size(); j++) {
			if (this->freqs[i].first == textclasifier.freqs[j].first) {
				score_value += abs(i - j);
				matches_is_founded = true;
				break;
			}
		}

		if (!matches_is_founded)
			score_value += MAX_SCORE;
	}

	return score_value;
}

//function for testing
void TextClasifier::print() const{
    for (auto const &pair: this->freqs) {
        std::cout << '{' << pair.first << "," << pair.second << '}' << std::endl;
    }
}