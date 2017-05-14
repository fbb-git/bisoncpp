#include "parser.ih"

void Parser::error()
{
    if (!d_error)
        cout << "At " << d_scanner.matched() << ": error in expression.\n"
                "(" << static_cast<int>(d_scanner.matched()[0]) << ")\n";
    d_error = true;
}
