#include "parser.ih"

void Parser::checkFirstType() 
{
    static string const STYPE("STYPE__");

    string const &stype = d_rules.sType();

    // the production has elements, but no action. 
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype or whether the rule's stype is empty (default)

    
    string const *firstStype = &d_rules.sType(1);

//    if (firstStype->empty())
//        firstStype = &STYPE;

    if (d_semType == POLYMORPHIC)
    {
        if (stype == STYPE && firstStype->empty())
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





