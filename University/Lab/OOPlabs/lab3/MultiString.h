/*!
* file: MultiString.h
* MultiString class definition
* written: 01/05/2012
* Copyright (c) 2012 by Yu.Zorin
*/
#pragma once
#include <string.h>
#include <stdio.h>
#include <iostream>


class MultiString{
public:
    //constructors destructor
    MultiString();
    MultiString(int );
    ~MultiString();

    //methods
    MultiString & operator = (const MultiString &ms){};
    char * operator[] (int nindex) const;
    MultiString & operator += (const MultiString &);
    void MergeMultiStringexclusive(const MultiString &);
    int Find(const char *pszsub ) const;
    int Getlength( ) const;
    bool Isempty()const{ return str_nmb == 0;};
    void Empty();
    void Setat( int nindex, const char* str );
    void Printstr(int nindex) const;
private:
    //forbidden copy constructor
    MultiString ( const MultiString & ms){};

    //attributes
    char **buf;//pointer to vector
    int str_nmb;//strings number
};
