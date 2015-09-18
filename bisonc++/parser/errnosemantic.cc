#include "parser.hh"

void Parser::errNoSemantic(char const *label, AtDollar const &atd,
                           string const &id) const
{
    emsg.setLineNr(atd.lineNr());
    emsg << "rule " << &d_rules.lastProduction() << ":\n"
            "\t\tsemantic " << label << " `" << id << 
            "' not defined (" << atd.text() << ")." << endl;
}
