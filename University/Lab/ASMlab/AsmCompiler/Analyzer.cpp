#include "Analazer.h"
#include "reservedData.h"
#include "stdio.h"
#include <string>
#include <iostream>

Analazer::Analazer()
{
    temp.clear();
    fileStr.clear();
}

Analazer::Analazer(std::string str)
{
    fileStr = str;
}

void Analazer::Analisis(char lastChar)
{
    if (isalpha(lastChar)) {
        if (!temp.empty())
            type = token_identifier;
        temp += lastChar;
        return;
    }
    if (isdigit(lastChar)) {
        if (!temp.empty())
            type = token_decnumber;
        // std::cout << "number";
        temp += lastChar;
        return;
    }
    // int asqiiChar = (int)lastChar;
    if ((lastChar == ' ') || (lastChar == '\n') || (lastChar == ',') && temp.empty()) {
        tokenAnalys(temp);
        // std::cout << "tokenAnalys is run";
        temp.clear();
        return;
    }
}

void Analazer::tokenAnalys(std::string str)
{
    switch (type) {
        case token_identifier:
            std::cout << str << " is token_identifier\n";
            type = token_nothing;
            break;
        case token_decnumber:
            std::cout << str << " is token_decnumber\n";
            type = token_nothing;
            break;

    } 
}

