#include "parser.ih"

void Parser::handleProductionElement(STYPE__ &last)
{
        // maybe also when currentRule == 0 ? See addProduction
    if (!d_rules.hasRules())    // may happen if the first rule could not be
        return;                 // defined because of token/rulename clash

    if (!last)         // the last PTag was a %prec specification
    {
        checkFirstType();
        return;
    }

    switch (last->tag())
    {
        case TERMINAL:
            d_rules.addElement(last->get<TERMINAL>());
            checkFirstType();
        break;
        case SYMBOL:
            d_rules.addElement(last->get<SYMBOL>());
            checkFirstType();
        break;
        case Tag__::BLOCK:
            installAction(last->get<Tag__::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }
}
