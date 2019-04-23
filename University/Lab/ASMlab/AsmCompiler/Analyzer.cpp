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
    index = 0;
}

Analazer::Analazer(std::string str)
{
    type = token_nothing;
    fileName = str;
    index = 0;
}

void Analazer::Start()
{
    std::ifstream file(this->fileName);
    std::string line;
    while (std::getline(file, line)) {
        line += "\n";
        std::cout << line << std::endl;
        for (int i = 0; i < line.length(); i++) {
            this->Analisis(line[i]);
        }
        std::cout << std::endl;
    }

    file.close();

}

void Analazer::GetFileName(std::string str)
{
    fileName = str;
}

void Analazer::Analisis(char lastChar)
{
    if (this->ReservedSymbolsSearch(arithmeticSymbols, lastChar)) {
        if (temp.empty()) {
            type = token_Symbol;
            temp += lastChar;
            tokenAnalys(temp);
            return;
        } else {
            tokenAnalys(temp);
            temp.clear();
            temp += lastChar;
            type = token_Symbol;
            tokenAnalys(temp);
            return;
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
    if (((lastChar == ' ') || (lastChar == '\n') || (lastChar == ','))) {
        tokenAnalys(temp);
        if (lastChar == '\n')
            index = 0;
        return;
    }
}

Analazer::Token Analazer::tokenAnalys(std::string str)
{
    switch (type) {
        case token_identifier:
            switch (identifierAnalysis(str, type))
            {
                case token_keyword:
                    std::cout << index << "  " << str << " is keyword. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_keyword;
                    break;
                case token_command:
                    std::cout << index << "  " << str << " is command. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_command;
                    break;
                case token_dataDirective:
                    std::cout << index << "  " << str << " is data directive. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_dataDirective;
                    break;
                case token_register:
                    std::cout << index << "  " << str << " is register. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_register;
                    break;
                default:
                    std::cout << index << "  " << str << " is identifier. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_identifier;
                    break;
            }
            break;
        case token_number:
            switch (str.back())
            {
                case 'b':
                    std::cout << index << "  " << str << " is bin number. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_binumber;
                    break;
                case 'h':
                    std::cout << index << "  " << str << " is hex number. Length: " << str.length() << std::endl; 
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_hexnumber;
                    break;
                default:
                    std::cout << index << "  " << str << " is dec number. Length: " << str.length() << std::endl;
                    type = token_nothing;
                    temp.clear();
                    index++;
                    return token_decnumber;
                    break;
            }
            break;
        case token_Symbol:
            std::cout << index << "  " << str << " is token_a. Length: "<< str.length() << std::endl;
            type = token_nothing;
            temp.clear();
            index++;
            return token_Symbol;
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

