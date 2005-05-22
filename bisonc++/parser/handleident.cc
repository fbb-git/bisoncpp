#include "parser.ih"

void Parser::handleIdent()
{
    nestedBlock();         // install a pending action first
        
    d_rules.addElement(useSymbol());
}


