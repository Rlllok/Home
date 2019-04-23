#include <string>

class Syntax{

private:
    enum Token {
        token_nothing,
        token_identifier,
        token_number,
        token_hexnumber,
        token_decnumber,
        token_binumber,
        token_arithmeticSymbol,
        token_keyword,
        token_command,
        token_dataDirective,
        token_register
    };

    Token type;
    std::string filename;
    std::string temp;

public:
    Syntax();
    Syntax(std::string);
    void lineAnalys(std::string);

};