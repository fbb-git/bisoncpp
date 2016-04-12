#include "parser.ih"

void Parser::warnMissingSemval() const
{
    string const &stype = d_rules.sType();

    if (stype.empty() or d_options.tagMismatches().value != Options::ON)
        return;

    wmsg << "`rule " << &d_rules.lastProduction() << 
                "': confirm action block returns a required " << 
                stype << " value" << endl;
}
