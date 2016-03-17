#include "parser.ih"

void Parser::missingSemval(Production const &prod, string const &stype) const
{
    emsg << "rule `" << &prod << "':\n"
            "    does not return required " << 
                (d_semType == POLYMORPHIC ? stype : "STYPE__"s) << 
                " value" << endl;
}
