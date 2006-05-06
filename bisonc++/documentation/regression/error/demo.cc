/*
                              error.cc
*/


#include <iostream>

#include "parser/Parser.h"

using namespace std;

int main(int argc, char **argv, char **envp)
{
    cout << "Enter lines, each containing one integral value. Use ^C to "
                                            "end the program\n"
            "other line content should result in a `syntax error'\n"
            "blanks and tabs are ignored (and thus OK)" << endl;

    Parser parser;

    parser.parse();

    return 0;
}
