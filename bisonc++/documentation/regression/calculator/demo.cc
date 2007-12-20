#include <iostream>

#include "parser/parser.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "Enter (integral) expressions on separate lines, using "
                                                        "+ - * / ()\n"
        "Other line content should result in a `syntax error'\n"
        "Blanks and tabs are ignored. Use ^c or ^d to end the program\n"
        "Use any program argument to view parser debug output\n";


    Parser calculator;
    calculator.setDebug(argc > 1);
    return calculator.parse();
}
