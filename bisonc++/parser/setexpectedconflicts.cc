#include "parser.ih"

void Parser::setExpectedConflicts()
{
    if (d_scanner.lex() != Scanner::NUMBER)
        lineMsg() << "%expect should be followed by a number" << err;

    Rules::setExpectedConflicts(d_scanner.number());
}
