#include "parser.ih"

void Parser::checkFirstType() 
{
    static string const STYPE("STYPE__");

    string const &stype = d_rules.sType();

    // the production has elements, but no action. 
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype.

    string const *firstStype = &d_rules.sType(1);

    if (firstStype->empty())
        firstStype = &STYPE;

    if (stype.length() && stype != *firstStype)
        wmsg << 
            "rule `" << d_rules.name() << "' type clash (`" << 
            stype << "' `" << *firstStype << "') on default action" << endl;
}
