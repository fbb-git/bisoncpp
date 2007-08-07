#include "parser.ih"

void Parser::error(char const *)
{
    if (!d_error)
        cout << "At " << d_scanner.YYText() << ": error in expression.\n"
                "(" << static_cast<int>(*d_scanner.YYText()) << ")\n";
    d_error = true;
}
