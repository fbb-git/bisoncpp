/*
                              example.cc
*/

#include <iostream>

#include "parser/parser.h"

using namespace std;

int main()
{
    cout << "Enter integral numbers or empty lines. ^C to stop\n";

    Parser parser;

    return parser.parse();
}
