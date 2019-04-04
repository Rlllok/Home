/************************************************************************
 * file: vectorFunctions.h
 * author: Novikov Alexander KV-72
 * written: 21/03/2019
 * last modified: 24/03/2019
 ************************************************************************/
#pragma once
#include <vector>
#include "CTranslate.h"

void ListAll(const std::vector<CTranslate>&);
void DelByEng(std::vector<CTranslate>&, const char*);
void DelByIta(std::vector<CTranslate>&, const char*);
void SortByEng(std::vector<CTranslate>&);
void SortByIta(std::vector<CTranslate>&);
void TranslateEng(std::vector<CTranslate>&, const char*);
void TranslateIta(std::vector<CTranslate>&, const char*);
