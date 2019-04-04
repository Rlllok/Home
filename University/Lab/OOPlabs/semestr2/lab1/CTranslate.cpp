/************************************************************************
 * file: CTranslate.cpp
 * CTranslate class realization
 * author: Novikov Alexander KV-72
 * written: 21/03/2019
 * last modified: 24/03/2019
 ************************************************************************/
#include "CTranslate.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>

CTranslate::CTranslate()
{
        eng = new char[64];
        ita = new char[64];
        eng[0] = '\0';
        ita[0] = '\0';
}

CTranslate::CTranslate(const CTranslate& ctranslate)
{
        eng = new char[64];
        ita = new char[64];
        strcpy(eng, ctranslate.eng);
        strcpy(ita, ctranslate.ita);
}

CTranslate::~CTranslate()
{
}

CTranslate& CTranslate::operator= (const CTranslate& ctranslate)
{
        strcpy(this->eng, ctranslate.eng);
        strcpy(this->ita, ctranslate.ita);
        return *this;
}

bool CTranslate::operator< (const CTranslate& ctranslate)
{
        if (strcmp(this->eng, ctranslate.eng) < 0)
                return true;
        else
                return false;
}

void CTranslate::MakePair(char* eng, char* ita)
{
        if(eng == NULL || ita ==  NULL)
                return;

        strcpy(this->eng, eng);
        strcpy(this->ita, ita);
}

void CTranslate::Print()const
{
        if (strlen(eng) == 0)
                std::cout << "Eng is empty" << '\n';
        if (strlen(ita) == 0)
                std::cout << "Ita is empty" << '\n';
        if ((strlen(ita) != 0) && (strlen(eng) != 0))
                std::cout << this->eng << " - " << this->ita << '\n';
}

char* CTranslate::GetEng()const
{
        return this->eng;
}

char* CTranslate::GetIta()const
{
        return this->ita;
}
