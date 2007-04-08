#include "parser/parser.h"

using namespace std;

int main(int argc)
{
    cout << "Enter (nested) expressions ONLY consisting of *, + and "
                                                    "unary - operators.\n"
        "The expressions are evaluated and converted to RPN notation\n"
        "Use int or double operands.  Blanks and tabs are ignored.\n"
        "Types are propagated over expressions, but all calculations are\n"
        "based on int values. An empty line ends the program.\n"
        "Use any program argument to view parser debug output\n";

    Parser parser;

    parser.setDebug(argc > 1);

    return parser.parse();
}
