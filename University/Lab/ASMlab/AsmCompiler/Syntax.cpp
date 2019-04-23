#include "Syntax.h"
#include <fstream>
#include <string>

Syntax::Syntax()
{
    type = token_nothing;
    temp.clear();
    filename.clear();
}

Syntax::Syntax(std::string filename)
{
    this->filename = filename;
    type = token_nothing;
    temp.clear();
}

void Syntax::lineAnalys(std::string line)
{
    line = line + "\n";
    for (int i = 0; i < line.length(); i++) {
        temp += line[i];
    }
}