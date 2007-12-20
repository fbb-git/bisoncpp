#include "parser/parser.h"

bool A2x::s_lastFail = false;

using namespace std;

int main(int argc, char **argv)
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
