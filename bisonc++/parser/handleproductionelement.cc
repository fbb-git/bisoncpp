#include "parser.ih"

    // See also README.polymorphic-technical

void Parser::handleProductionElement(STYPE__ &last)
{
        // maybe also when currentRule == 0 ? See addProduction
    if (!d_rules.hasRules())    // may happen if the first rule could not be
        return;                 // defined because of token/rulename clash

// cerr << "handleproductionelement\n";

    if (!last)         // the last PTag was a %prec specification
    {
// cerr << "   last\n";
        checkFirstType();
        return;
    }


    switch (last.tag())
    {
        case Tag__::TERMINAL:
// cerr << "   terminal\n";
            d_rules.addElement(last.get<Tag__::TERMINAL>());
            checkFirstType();
        break;
        case Tag__::SYMBOL:
// cerr << "   symbol\n";
            d_rules.addElement(last.get<Tag__::SYMBOL>());
            checkFirstType();
        break;
        case Tag__::BLOCK:
// cerr << "   block\n";
            installAction(last.get<Tag__::BLOCK>());
        break;

        default:            // can't occur, but prevents a warning
        break;              // from the compiler
    }

//    Production const &lastProd = d_rules.lastProduction();
//
//    if (not lastProd.action().empty())
//    {
//        if (not lastProd.action().usedDollarDollar())
//            missingSemval(lastProd);
//
//        return;
//    }
//
//    addDefaultAction(lastProd);
}






