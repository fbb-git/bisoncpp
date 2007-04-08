#include <iostream>
#include <string>

#include "parser/parser.h"

using namespace std;

int main(int argc)
{
    cout << "Enter numbers separated by semicolons. Blanks and tabs are "
                                                                "ignored.\n"
        "^c or ^d  ends the program.\n"
        "Use any program argument to view parser debug output\n";

    Parser parser;
    parser.setDebug(argc > 1);
    return parser.parse();
}
