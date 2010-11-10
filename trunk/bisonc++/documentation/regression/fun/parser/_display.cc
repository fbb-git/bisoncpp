#include "parser.ih"

void Parser::display(RuleValue const &e)
{
    if (!d_error)
        cout << rvalue(e) << '\n';
}
