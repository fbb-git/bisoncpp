#include "parser.ih"

void Parser::error(bool ifTrue, char const *msg)
{
    if (d_error || not ifTrue)
        return;

    d_error = true;
    cout << msg << '\n';
    ERROR();
}
