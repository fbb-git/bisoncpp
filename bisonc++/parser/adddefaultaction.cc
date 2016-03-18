#include "parser.ih"

void Parser::addDefaultAction(Production const &prod) 
{
    if (d_options.defaultActions().value == Options::OFF)
    {
        if (d_options.tagMismatches().value == Options::ON)
            wmsg << '`' << &prod << "':\n"
                    "    configuration prevents adding $$ = $1 "
                                                    "action block" << endl;

        return;                     // no default action. Hope it's OK...
    }

    string const &stype = d_rules.sType();

    int idx = prod.size();

    if (idx > 0 && stype != prod[0].sType()) 
    {
        emsg << '`' << &prod << "':\n"
            "    type mismatch: can't add $$ = $1 action block" << endl;
        return;
    }

    if (d_semType != SINGLE && stype.empty())   // union or polymorphic but
        return;                                 // no associated value type:
                                                // no action block required.

    if (d_options.defaultActions().value == Options::WARN)
        wmsg << '`' << &prod << "':\n"
                    "    adding $$ = $1 action block" << endl;

    Block block;
    block.open(prod.lineNr(), prod.fileName());

    block += "\n"
            "    d_val__ = ";

    block += 
        idx != 0?                   // production not empty
            "d_vsp__[" + to_string(1 - idx) + "];"
        :
        (                           // empty production
            d_semType == POLYMORPHIC ?
                "Meta__::TypeOf<Tag__::" + stype + ">::type{};"
            :
                "STYPE__{}"s
        );

    block += "\n}";

    d_rules.setAction(block);
}
