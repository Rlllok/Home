/************************************************************************
 * file: CTranslate.h
 * CTranslate class declaration
 * author: Novikov Alexander KV-72
 * written: 21/03/2019
 * last modified: 24/03/2019
 ************************************************************************/
#pragma once

class CTranslate
{
public:
        CTranslate();
        CTranslate(const CTranslate &);
        ~CTranslate();

        CTranslate& operator= (const CTranslate&);
        bool operator< (const CTranslate&);
        void MakePair(char*, char*);
        void Print()const;
        char* GetEng()const;
        char* GetIta()const;
private:
        char* eng;
        char* ita;
};
