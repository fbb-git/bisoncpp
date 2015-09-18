#include "parser.hh"

void Parser::display(RuleValue const &e)
{
    if (!d_error)
        cout << rvalue(e) << '\n';
}
