#pragma once
#include <string>

class Analazer {
private:
    enum Token {
        token_nothing,
        token_identifier,
        token_hexnumber,
        token_decnumber,
        token_binumber
    };
    
    std::string temp;
    std::string fileStr;
    Token type = token_nothing;

public:
    void StrToCharConverter(std::string);
    void Analisis(char);
    void tokenAnalys(std::string);
    void StrToChar(std::string);
    Analazer();
    Analazer(std::string);
};
