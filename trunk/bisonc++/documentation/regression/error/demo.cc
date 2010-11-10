/*
                              error.cc
*/


#include <iostream>

#include "parser/Parser.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Enter lines, each containing one integral value.\n"
            "Other lines (also empty lines) should result in a "
                                                        "`syntax error'\n"
            "Blanks and tabs are ignored. Use ^c or ^d to end the program\n"
            "Use any program argument to view parser debug output\n";

    Parser parser;

    parser.setDebug(argc > 1);
    parser.parse();

    return 0;
}

