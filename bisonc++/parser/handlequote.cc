#include "parser.ih"

void Parser::handleQuote()
{
    nestedBlock();         // install a pending action first

    d_rules.addElement(useTerminal());
}
