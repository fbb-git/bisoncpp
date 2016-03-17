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

    string const &stype = d_rules.sType();

    if (stype.empty())              // no semantic type: no action needed
        return;
    
    Production const &lastProd = d_rules.lastProduction();

    if (not lastProd.action().empty())
    {
        if (not lastProd.action().usedDollarDollar())
            missingSemval(lastProd, stype);

        return;
    }

    if (not d_options.defaultActions())
    {
        if (not lastProd.action().usedDollarDollar())
            missingSemval(lastProd, stype);
        return;
    }

    Block block;
    block.open(lastProd.lineNr(), lastProd.fileName());

    int idx = 1 - lastProd.size();

    block += "\n" 
                "  d_val__ = d_vsp__[" + to_string(idx) + "];"
            + "\n}";


    d_rules.setAction(block);

    string firstType = lastProd[0].sType();
        
    if (stype == firstType)
        wmsg << "rule `" << &lastProd << 
                                "': added $$ = $1 assignment" << endl;
    else
    {
        if (firstType.empty())
            firstType = "(token)";

        emsg << "rule `" << &lastProd << "':\n"
            "    cannot add assignment " << firstType << " (= $1) to " << 
            stype << " (= $$)" << endl;
    }
}






