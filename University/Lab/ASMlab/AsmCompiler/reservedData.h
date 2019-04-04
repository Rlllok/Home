#pragma once
#include <string>
#include <vector>

std::vector<char> arithmeticSymbols = {'+', '-', '*', '(', ')', '[', ']', ':'};
std::vector<char> punctuationSymbols = {',', ':', ' '};
std::vector<std::string> keyWords = {
    "segment",
    "ends",
    "end"
};
std::vector<std::string> commands = {
    "stc",
    "inc",
    "dec",
    "sub",
    "and",
    "or",
    "mov",
    "cmp",
    "jbe"
};
std::vector<std::string> dataDirectives = {
    "dd",
    "dw",
    "db"
};
std::vector<std::string> registers = {
    "eax",
    "ebx",
    "esi",
    "ebp",
    "edx",
    "ecx"
};
