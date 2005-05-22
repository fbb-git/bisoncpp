/*
                              demo.cc
*/

#include "demo.h"

int main(int argc, char **argv, char **envp)
{
    Parser parser;

    cout << "Parser returns " << parser.parse() << endl;

    return 0;
}
