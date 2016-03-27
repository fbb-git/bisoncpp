#include "parser.ih"

    // See also README.polymorphic-technical

void Parser::handleProductionElement(STYPE__ &last)
{
        // maybe also when currentRule == 0 ? See addProduction
    if (!d_rules.hasRules())    // may happen if the first rule could not be
        return;                 // defined because of token/rulename clash

    if (not last.valid())        // the last PTag was a %prec specification
    {
        checkFirstType();
        return;
    }

    switch (last.tag())
    {
        case Tag__::TERMINAL:
            d_rules.addElement(last.get<Tag__::TERMINAL>());
            checkFirstType();
        break;
        case Tag__::SYMBOL:
            d_rules.addElement(last.get<Tag__::SYMBOL>());
            checkFirstType();
        break;
        case Tag__::BLOCK:
            installAction(last.get<Tag__::BLOCK>());
        break;

        default:            // can't occur, but prevents a warning
        break;              // from the compiler
    }
}






