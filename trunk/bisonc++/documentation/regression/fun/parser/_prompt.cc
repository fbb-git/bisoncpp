#include "parser.ih"

void Parser::prompt()
{
    cout << "? " << flush;
    d_error = false;
}
