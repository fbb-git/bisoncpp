#include "parser.ih"

    // the production for which this member is called has elements, 
    // but does not define an action block.
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype or whether the rule's stype is empty (default)
    
void Parser::checkFirstType() 
{
    Production const &prod = d_rules.lastProduction();

    if (d_options.defaultActions().value == Options::OFF)
    {
        if (d_options.tagMismatches().value == Options::ON)
            wmsg << '`' << &prod << "': auto-appending `$$ = $1' action "
                "block suppressed by configuration "
                "(default-actions off)" << endl;

        return;                     // no default action. Hope it's OK...
    }

    string const &stype = d_rules.sType();

    int idx = prod.size();

    string const &prodStype = prod[0].sType();

    if (d_semType != SINGLE && stype.empty())   // union or polymorphic but
        return;                                 // no associated value type:
                                                // no action block required.
    if (idx > 0 && stype != prodStype) 
    {
        emsg << '`' << &prod << "':  type clash ($$: " << stype << ", $1: " <<
                (prodStype.empty() ? "<undefined>"s : prodStype) <<
                " prevents auto-appending default action `$$ = $1'" << endl;
        return;
    }

    if (d_options.defaultActions().value == Options::WARN)
        wmsg << '`' << &prod << "': auto-appended `$$ = $1' action block" << 
                                                                        endl;

    Block block;
    block.open(prod.lineNr(), prod.fileName());

    block += "\n"
            "    ";
    block += s_semanticValue;
    block += " = ";

    block += 
        idx != 0?                   // production not empty
            string{s_semanticValueStack} + '[' + to_string(1 - idx) + "];"
        :
        (                           // empty production
            d_semType == POLYMORPHIC ?
                "Meta__::TypeOf<Tag__::" + stype + ">::type{}"
            :
                s_stype__ + "{}"s
        );

    block += ";\n}";

    d_rules.setAction(block);
}





