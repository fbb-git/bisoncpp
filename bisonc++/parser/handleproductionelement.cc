#include "parser.ih"

    // See also README.polymorphic-technical

void Parser::handleProductionElement(STYPE_ &last)
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
        case Tag_::TERMINAL:
            d_rules.addElement(last.get<Tag_::TERMINAL>());
            checkFirstType();
        break;
        case Tag_::SYMBOL:
            d_rules.addElement(last.get<Tag_::SYMBOL>());
            checkFirstType();
        break;
        case Tag_::BLOCK:
            installAction(last.get<Tag_::BLOCK>());
        break;

        default:            // can't occur, but prevents a warning
        break;              // from the compiler
    }
}






