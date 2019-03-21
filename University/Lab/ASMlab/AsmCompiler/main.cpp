#include "Analazer.h"
#include <iostream>
#include "string.h"

int main()
{
    std::string str = "mov      eax,         12\n";
    Analazer scanner(str);
    int length = str.length();
    length;
    char char_array[length + 1];
    strcpy(char_array, str.c_str());

    for (int i = 0; i < length; i++) {
        scanner.Analisis(str[i]);
    }

    return 0;
}
