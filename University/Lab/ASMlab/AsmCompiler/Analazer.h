#pragma once
#include <string>
#include <vector>

class Analazer {
private:
    enum Token {
        token_nothing,
        token_identifier,
        token_number,
        token_hexnumber,
        token_decnumber,
        token_binumber,
        token_Symbol,
        token_keyword,
        token_command,
        token_dataDirective,
        token_register
    };
    
    std::string temp;
    std::string fileName;
    Token type;
    int index;

public:
    Analazer();
    Analazer(std::string);
    void Start();
    void GetFileName(std::string);
    void StrToCharConverter(std::string);
    void Analisis(char);
    Token tokenAnalys(std::string);
    void StrToChar(std::string);
    bool ReservedDataSearch(std::vector<std::string>, std::string);
    bool ReservedSymbolsSearch(std::vector<char>, char);
    Token identifierAnalysis(std::string, Token);
};
