#include "parser.ih"

Parser::STYPE__ Parser::handleProductionElements(STYPE__ &first, 
                                                 STYPE__ const &second)
{
    if (!first)         // the first PTag was a %prec specification
        return second;  
    if (!second)        // the second PTag was a %prec specification:
        return first;   // postpone handling of first

        // maybe also when currentRule == 0 ? See addProduction
    if (!d_rules.hasRules())    // may happen if the first rule could not be
        return first;           // defined because of token/rulename clash

    switch (first->tag())
    {
        case TERMINAL:
            d_rules.addElement(first.get<TERMINAL>());
        break;
        case SYMBOL:
            d_rules.addElement(first.get<SYMBOL>());
        break;
        case Tag__::BLOCK:
            nestedBlock(first.get<Tag__::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }

    return second;
}


