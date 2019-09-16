/************************************************************************       
 * file: main.cpp                                              
 * author: Novikov Alexander KV-72                                              
 * written: 03/06/2019                                                          
 * last modified: 04/06/2019                                                    
 ************************************************************************/
#include "TextClasifier.h"

int main() {
	const int languages_count = 4;
	std::string languages[languages_count] = {"English", "French", "Spanish", "Italian"};
	TextClasifier textclasifier[languages_count];
	int min = 0, n;
	std::ifstream test;
    std::string filename;

    std::cout << "Input filename: ";
    //test1 - ENGLISH
    //test2 - FRENCH
    //test3 - SPANISH
    //test4 - ITALIAN
    std::cin >> filename;

    test.open(filename);
    if (!test.is_open()) {
        std::cout << "Wrong file" << std::endl;
        exit(1);
    }

	TextClasifier match_lang;

	match_lang.learn(test);
	test.close();

	for (int i = 0; i < languages_count; i++) {
		std::ifstream in_lang(languages[i] + ".txt");
		std::ofstream out_lang(languages[i] + "Dump.txt");
		if (!in_lang.is_open()) {
			std::cout << "file " << languages[i] << "was not found" << std::endl;
			exit(1);
		}

		textclasifier[i].setCategory(languages[i]);
		textclasifier[i].learn(in_lang);
		textclasifier[i].dumpProfile(out_lang);
		in_lang.close();
	}

	int min_sc = textclasifier[0].score(match_lang), cur_sc;

	for (int i = 0; i < languages_count; i++) {
		cur_sc = textclasifier[i].score(match_lang);
		if (cur_sc < min_sc)
		{
			min = i;
			min_sc = cur_sc;
		}
	}
	std::cout << "\tIt is "<< textclasifier[min].getCategory() << " text." << std::endl;

	return 0;
}