#include "parser.ih"

Parser::STYPE__ Parser::handleProductionElements(STYPE__ &first, 
                                                 STYPE__ const &second)
{
    if (not first.valid())      // the first PTag was a %prec specification
        return second;  
    if (not second.valid())     // the second PTag was a %prec specification:
        return first;   // postpone handling of first

        // maybe also when currentRule == 0 ? See addProduction
    if (!d_rules.hasRules())    // may happen if the first rule could not be
        return first;           // defined because of token/rulename clash

    switch (first.tag())
    {
        case Tag__::TERMINAL:
            d_rules.addElement(first.get<Tag__::TERMINAL>());
        break;
        case Tag__::SYMBOL:
            d_rules.addElement(first.get<Tag__::SYMBOL>());
        break;
        case Tag__::BLOCK:
            nestedBlock(first.get<Tag__::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }

    return second;
}


