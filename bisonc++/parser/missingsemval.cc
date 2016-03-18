#include "parser.ih"

void Parser::missingSemval(Production const &prod) const
{
    string const &stype = d_rules.sType();

    if (stype.empty() or d_options.tagMismatches().value != Options::ON)
        return;

    wmsg << '`' << &prod << "':\n"
            "    might not return a required " << stype << " value" << endl;
}
