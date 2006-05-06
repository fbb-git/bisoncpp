/*
                              demo.cc
*/

#include <iostream>

#include "parser/parser.h"

using namespace std;


int main(int argc, char **argv, char **envp)
{

    cout << "Enter lines containing  NR + NR =   or  q  to stop\n"
            "The numbers should be integral numbers." << endl;

    Parser parser;

    cout << "Parser returns " << parser.parse() << endl;
    return 0;
}


