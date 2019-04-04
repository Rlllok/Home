#include "Analazer.h"
#include "reservedData.h"
#include "stdio.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

Analazer::Analazer()
{
    temp.clear();
    type = token_nothing;
}

Analazer::Analazer(std::string str)
{
    type = token_nothing;
    fileName = str;
}

void Analazer::GetFileName(std::string str)
{
    fileName = str;
}

void Analazer::Start()
{
    std::ifstream file(this->fileName);
    char c;
    while (file.get(c)) {
        this->Analisis(c);
    }
    if (!temp.empty()) {
        tokenAnalys(temp);
    }

    file.close();
}

void Analazer::Analisis(char lastChar)
{
    if (this->ReservedSymbolsSearch(arithmeticSymbols, lastChar)) {
        if (temp.empty()) {
            type = token_arithmeticSymbol;
            temp += lastChar;
            tokenAnalys(temp);
        } else {
            tokenAnalys(temp);
            temp.clear();
            temp += lastChar;
            type = token_arithmeticSymbol;
            tokenAnalys(temp);
        }
    }
    if (isalpha(lastChar)) {
        if (temp.empty())
            type = token_identifier;
        temp += lastChar;
        return;
    }
    if (isdigit(lastChar)) {
        if (temp.empty())
            type = token_number;
        temp += lastChar;
        return;
    }
    if (((lastChar == ' ') || (lastChar == '\n') || (lastChar == ',')) && !temp.empty()) {
        tokenAnalys(temp);
        return;
    }
}

void Analazer::tokenAnalys(std::string str)
{
    switch (type) {
        case token_identifier:
            switch (identifierAnalysis(str, type))
            {
                case token_keyword:
                    std::cout << str << " is keyword. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
                case token_command:
                    std::cout << str << " is command. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
                case token_dataDirective:
                    std::cout << str << " is data directive. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
                case token_register:
                    std::cout << str << " is register. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
                default:
                    std::cout << str << " is identifier. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
            }
            break;
        case token_number:
            switch (str.back())
            {
                case 'b':
                    std::cout << str << " is bin number. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
                case 'h':
                    std::cout << str << " is hex number. Length: " << str.length() << std::endl; 
                    type = token_nothing;
                    temp.clear();
                    break;
                default:
                    std::cout << str << " is dec number. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    break;
            }
            break;
        case token_arithmeticSymbol:
            std::cout << str << " is token_a. Length: "<< str.length() << std::endl;
            type = token_nothing;
            temp.clear();
            break;
    } 
}

Analazer::Token Analazer::identifierAnalysis(std::string str, Token token_type)
{
    if (token_type != token_identifier) return token_type;

    if (ReservedDataSearch(keyWords, str)) {
        return token_keyword;
    } else if (ReservedDataSearch(commands, str)) {
        return token_command;
    } else if (ReservedDataSearch(dataDirectives, str)) {
        return token_dataDirective;
    } else if (ReservedDataSearch(registers, str)) {
        return token_register;
    } else {
        return token_identifier;
    }
}

bool Analazer::ReservedDataSearch(std::vector<std::string> stringVector, std::string temp)
{
    if (std::find(stringVector.begin(), stringVector.end(), temp) != stringVector.end()) {
        return true;
    } else return false;
}

bool Analazer::ReservedSymbolsSearch(std::vector<char> charVector, char symbol)
{
    if (std::find(charVector.begin(), charVector.end(), symbol) != charVector.end()) {
        return true;
    } else return false;
}
