/************************************************************************
 * file: vectorFunctions.cpp
 * author: Novikov Alexander KV-72
 * written: 21/03/2019
 * last modified: 24/03/2019
 ************************************************************************/
#include "vectorFunctions.h"
#include <iostream>
#include "string.h"
#include <algorithm>


void ListAll(const std::vector<CTranslate>& vCtranslate)
{
        for (auto iter = vCtranslate.begin(); iter != vCtranslate.end(); iter++)
                iter->Print();
}

void DelByEng(std::vector<CTranslate>& vCtranslate, const char* eng)
{
        if (eng == NULL)
                return;

        for (auto iter = vCtranslate.cbegin(); iter != vCtranslate.end(); iter++) {
                if (strcmp(iter->GetEng(), eng) == 0){
                        vCtranslate.erase(iter);
                        iter = vCtranslate.begin();
                }
        }
}

void DelByIta(std::vector<CTranslate>& vCtranslate, const char* ita)
{
        if (ita == NULL)
                return;

        for (auto iter = vCtranslate.cbegin(); iter != vCtranslate.end(); iter++) {
                if (strcmp(iter->GetIta(), ita) == 0){
                        vCtranslate.erase(iter);
                        iter = vCtranslate.begin();
                }
        }
}

void SortByEng(std::vector<CTranslate>& vCtranslate)
{
        std::sort(vCtranslate.begin(), vCtranslate.end());
}

void SortByIta(std::vector<CTranslate>& vCtranslate)
{
        struct ItaLess {
                bool operator() (const CTranslate& ctranslate1, const CTranslate& ctranslate2) {
                        if (strcmp(ctranslate1.GetIta(), ctranslate2.GetIta()) < 0)
                                return true;
                        else
                                return false;
                }
        };
        std::sort(vCtranslate.begin(), vCtranslate.end(), ItaLess());
}

void TranslateEng(std::vector<CTranslate>& vCtranslate, const char* eng)
{
        if (eng == NULL)
                return;

        std::cout << eng << ":" << '\n';
        for (auto iter = vCtranslate.begin(); iter != vCtranslate.end(); iter++) {
                if (strcmp(iter->GetEng(), eng) == 0) {
                        std::cout << "\t" << iter->GetIta() << '\n';
                }
        }
}

void TranslateIta(std::vector<CTranslate>& vCtranslate, const char* ita)
{
        if (ita == NULL)
                return;
        std::cout << ita << ":" << '\n';
        for (auto iter = vCtranslate.begin(); iter != vCtranslate.end(); iter++) {
                if (strcmp(iter->GetIta(), ita) == 0) {
                        std::cout << "\t" << iter->GetEng() << '\n';
                }
        }
}
