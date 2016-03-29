#include "parser.ih"

    // the production for which this member is called has elements, 
    // but does not define an action block.
    // Now check if the production's FIRST element's stype is equal
    // to the rule's stype or whether the rule's stype is empty (default)
    
void Parser::checkFirstType() 
{
    Production const &prod = d_rules.lastProduction();

    switch (d_options.defaultActions().value)
    {
        case Options::OFF:
            if (d_options.tagMismatches().value == Options::ON)
                wmsg << '`' << &prod << "': auto-appending `$$ = ...' "
                    "action block suppressed by option/directive "
                    "`default-actions off'" << endl;

        return;                     // no default action. Hope it's OK...

        case Options::WARN:
            wmsg << '`' << &prod << 
                    "': auto-appended `$$ = $1' action block" << endl;
        break;

        default:
        break;
    }

    size_t nElements = prod.size();
    string const &ruleType = d_rules.sType();

    if (nElements && d_semType == POLYMORPHIC)   // check for mismatches between
    {                                       // $$'s type and $1's type
        string const &firstElementType = prod[0].sType();

        if (ruleType != firstElementType) 
        {
            emsg << '`' << &prod << "':  type clash ($$: " << 
                ruleType << ", $1: " <<
                (firstElementType.empty() ? s_undefined : firstElementType) <<
                ") prevents auto-appending default action `$$ = ...'" << endl;
            return;
        }
    }

    Block block;
    block.open(prod.lineNr(), prod.fileName());

    block += "\n"
        "    " + s_semanticValue + " = " +
        (
            nElements > 0 ?
                svsElement(nElements, 1)
            :
            (                           // empty production
                d_semType == POLYMORPHIC ?
                    "Meta__::TypeOf<Tag__::" + ruleType + ">::type{}"
                :
                    s_stype__ + "{}"s
            )
        ) + ";\n"
        "}";

    d_rules.setAction(block);
}





