#include "parser.hh"

void Parser::checkEmptyBlocktype() 
{
    string const &stype = d_rules.sType();

    if (stype.size())           // return type is required
        wmsg << 
            "rule `" << &d_rules.lastProduction() <<
            "': no " << d_rules.sType() << " value is returned from this "
            "empty production rule" << endl;
}

