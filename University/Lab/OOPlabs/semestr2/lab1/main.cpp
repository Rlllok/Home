/************************************************************************
 * file: main.cpp
 * author: Novikov Alexander KV-72
 * written: 21/03/2019
 * last modified: 24/03/2019
 ************************************************************************/
#include "CTranslate.h"
#include "vectorFunctions.h"
#include "iostream"
#include <vector>
#include <fstream>
#include <string>
#include "string.h"

int main()
{
        char eng[64];
        eng[0] = '\0';
        char ita[64];
        ita[0] = '\0';
        char eng1[64] = "nice";
        char ita1[64] = "bella";
        char eng2[64] = "lazy";
        char ita2[64] = "pigro";

        CTranslate ctranslate1;
        CTranslate ctranslate2;
        std::cout << "= operator overload test: " << '\n';
        ctranslate1.MakePair(eng1, ita1);
        ctranslate2.MakePair(eng2, ita2);
        std::cout << "\tctranslate1: ";
        ctranslate1.Print();
        std::cout << "\tctranslate2: ";
        ctranslate2.Print();
        std::cout << "\tctranslate1 after ctranslate1 = ctranslate2: ";
        ctranslate1 = ctranslate2;
        ctranslate1.Print();
        ctranslate1.MakePair(eng1, ita1);
        std::cout << '\n';

        std::cout << "< operator overload test: " << '\n';
        ctranslate1.MakePair(eng1, ita1);
        ctranslate2.MakePair(eng2, ita2);
        std::cout << "\tctranslate1: ";
        ctranslate1.Print();
        std::cout << "\tctranslate2: ";
        ctranslate2.Print();
        std::cout << "\tctranslate1 < ctranslate2 result: ";
        std::cout << (ctranslate1 < ctranslate2) << '\n';
        ctranslate1.Print();
        std::cout << '\n';

        std::cout << "GetEng and GetIta test: " << '\n';
        ctranslate1.MakePair(eng1, ita1);
        std::cout << "\tctranslate1: ";
        ctranslate1.Print();
        std::cout << "\tGetEng: " << ctranslate1.GetEng() << '\n';
        std::cout << "\tGetIta: " << ctranslate1.GetIta() << '\n';
        ctranslate1.Print();
        std::cout << '\n';


        std::vector<CTranslate> vCtranslate;
        bool isRepeated = false;

        std::string word, line, filename;
        filename = "words.csv";
        std::ifstream csvFile("words.csv");

        if (!csvFile.is_open()) {
                std::cout << "FILE Error" << '\n';
                exit(0);
        }

        while (getline(csvFile, word, ';'))
        {
                strcpy(eng, word.c_str());
                getline(csvFile, word, '\n');
                strcpy(ita, word.c_str());
                CTranslate buff;
                buff.MakePair(eng, ita);
                for (auto iter = vCtranslate.begin(); iter != vCtranslate.end(); iter++) {
                        if ((strcmp(iter->GetEng(), buff.GetEng()) == 0) && (strcmp(iter->GetIta(), buff.GetIta()) == 0))
                                isRepeated = true;
                }
                if (isRepeated != true)
                        vCtranslate.push_back(CTranslate(buff));
                isRepeated = false;
        }
        csvFile.close();

        std::cout << "Vector: " << '\n';
        ListAll(vCtranslate);
        std::cout << "SortByEng test: " << '\n';
        SortByEng(vCtranslate);
        std::cout << "Vector after SortByEng: " << '\n';
        ListAll(vCtranslate);

        std::cout << "Vector: " << '\n';
        ListAll(vCtranslate);
        std::cout << "SortByIta test: " << '\n';
        SortByIta(vCtranslate);
        std::cout << "Vector after SortByIta: " << '\n';
        ListAll(vCtranslate);

        std::cout << "Vector: " << '\n';
        ListAll(vCtranslate);
        std::cout << "DelByEng test: " << '\n';
        DelByEng(vCtranslate, "lazy");
        std::cout << "Vector after \"nice\" delete: " << '\n';
        ListAll(vCtranslate);

        std::cout << "Vector: " << '\n';
        ListAll(vCtranslate);
        std::cout << "DelByIta test: " << '\n';
        DelByIta(vCtranslate, "luna");
        std::cout << "Vector after \"luna\" delete: " << '\n';
        ListAll(vCtranslate);

        std::cout << "TranslateEng test:" << '\n';
        std::cout << "\"Nice\" translate:" << '\n';
        TranslateEng(vCtranslate, "nice");

        std::cout << "TranslateIta test:" << '\n';
        std::cout << "\"Bella\" translate:" << '\n';
        TranslateIta(vCtranslate, "bella");




        return 0;
}
