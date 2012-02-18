#include "parser.ih"

spSemBase Parser::handleProductionElements(spSemBase const &first, 
                                           spSemBase const &second)
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
        case Tag::TERMINAL:
            d_rules.addElement(first->as<Tag::TERMINAL>());
        break;
        case Tag::SYMBOL:
            d_rules.addElement(first->as<Tag::SYMBOL>());
        break;
        case Tag::BLOCK:
            nestedBlock(first->as<Tag::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }

    return second;
}


