#include "parser/parser.h"

using namespace std;

int main()
{
    Parser parser;

    cout << "Enter (nested) expressions ONLY consisting of *, + and "
            "unary - operators,\n"
            "Use int or double operands.\n"
            "An empty line ends the program.\n";

    return parser.parse();
}
