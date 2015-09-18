#include "parser.hh"

    // the production has elements, but no action. 
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype or whether the rule's stype is empty (default)
    
void Parser::checkFirstType() 
{
    string const &stype = d_rules.sType();

    string const *firstStype = &d_rules.sType(1);

    if (d_semType == POLYMORPHIC)
    {
        if (stype == s_stype__ && firstStype->empty())
            wmsg << 
                "rule `" << &d_rules.lastProduction() << ":\n"
                "\t\texplicitly tagged or `STYPE__' semantic value "
                                                    "expected" << endl;
    }
    else if (stype.length() && stype != *firstStype)
        wmsg << 
            "rule `" << d_rules.name() << "' type clash (`" << 
            stype << "' `" << *firstStype << "') on default action" << endl;
}





