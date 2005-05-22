#include "parser.ih"

void Parser::checkBlocktype() 
{
    string const &stype = d_rules.sType();

    if (!d_rules.nProductions())    // an empty alternative, 
    {
        if (stype.size())           // but return type ($1) is required
            lineMsg() << 
                "rule `" << d_rules.name() << 
                "': empty alternative lacks return type" << warning;
    }
    else if (!d_block.length())
    {
        // the production has elements, but no action. 
        // Now check if the production's FIRST element's stype is equal
        // to the rule's stype.

        string const &firstStype = d_rules.sType(0);

        if (stype != firstStype)
            lineMsg() << 
                "rule `" << d_rules.name() << "' type clash (`" << 
                stype << "' `" << firstStype << "') on default action" << 
                warning;
    }
}
