#include "parser.ih"

Parser::STYPE_ Parser::handleProductionElements(STYPE_ &first, 
                                                 STYPE_ const &second)
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
        case Tag_::TERMINAL:
            d_rules.addElement(first.get<Tag_::TERMINAL>());
        break;
        case Tag_::SYMBOL:
            d_rules.addElement(first.get<Tag_::SYMBOL>());
        break;
        case Tag_::BLOCK:
            nestedBlock(first.get<Tag_::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }

    return second;
}


