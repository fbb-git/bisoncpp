#include <iostream>

#include "parser/parser.h"

using namespace std;

int main()
{
    cout << "Enter (integral) expressions on separate lines, using "
                                                        "+ - * / ()\n"
            "Enter q to quit\n";

    Parser calculator;
    return calculator.parse();
}
