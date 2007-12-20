#include <iostream>
#include <string>

#include "parser/parser.h"
using namespace std;

int main(int argc, char **argv)
{
    Parser parser;

    cout << "Enter expressions on separate lines\n"
        "Enter the command   help   for an overview of the program's "
                                                            "features\n"
        "Use quit, or ^c to end the program\n"
        "Use any program argument to view parser debug output\n";

    parser.setDebug(argc > 1);
    parser.parse();

    return 0;
}
