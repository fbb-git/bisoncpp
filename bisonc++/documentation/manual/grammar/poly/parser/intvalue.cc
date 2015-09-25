#include "parser.ih"

int Parser::intValue() const
{
    istringstream in(d_scanner.matched());
    int ret;

    in >> ret;  // succeeds, as lex() just returned 'NR'
    return ret;
}
