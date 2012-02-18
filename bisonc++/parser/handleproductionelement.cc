#include "parser.ih"

void Parser::handleProductionElement(spSemBase const &last)
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
        case Tag::TERMINAL:
            d_rules.addElement(last->as<Tag::TERMINAL>());
            checkFirstType();
        break;
        case Tag::SYMBOL:
            d_rules.addElement(last->as<Tag::SYMBOL>());
            checkFirstType();
        break;
        case Tag::BLOCK:
            installAction(last->as<Tag::BLOCK>());
        break;

        default:            // can't occur, but used to keep the 
        break;              // compiler from generating a warning
    }
}
