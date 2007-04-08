#include "parser.ih"

void Parser::handleQuote()
{
    nestedBlock();         // install a pending action first

    d_rules.addElement(useTerminal());

    if (d_scanner.number() & (1 << 8))
        lineMsg() << "multiple characters in quoted constant " << 
                    d_scanner.text() << err;
}
