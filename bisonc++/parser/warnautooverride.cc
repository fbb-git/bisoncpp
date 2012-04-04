#include "parser.ih"

void Parser::warnAutoOverride(char const *typeOrField, 
                              AtDollar const &atd) const
{
    wmsg.setLineNr(atd.lineNr());
    wmsg << &d_rules.lastProduction() << ": `" << atd.text() << "' overrides "
            "auto " << typeOrField << forcing `%type <" << override << 
            ">' in `" atd.text() << '\'' << endl;
}
