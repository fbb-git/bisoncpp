#include "parser.ih"

    // encountered a rule w/o action block

void Parser::checkEmptyBlocktype() 
{
    string const &stype = d_rules.sType();

    if (stype.empty())              // no semantic type: no action needed
        return;

    Production const &last = d_rules.lastProduction();

    if (not d_options.defaultActions()) // no default action requested
    {
        missingSemval(last, stype);
        return;
    }

    Block block;
    block.open(last.lineNr(), last.fileName());

    
    block += "\n" +
        (
            d_semType == POLYMORPHIC ?
            "  d_val__ = Meta__::TypeOf<Tag__::" + stype + ">::type{};"
        :
            "  d_val__ = STYPE__{}"s
        ) 
        + "\n}";

    d_rules.setAction(block);

    wmsg << "rule `" << &last << "':\n"
            "    added $$ = " <<
            (
                d_semType == POLYMORPHIC ?
                    "Meta__::TypeOf<Tag__::" + stype + ">::type{}"
                :
                    "STYPE__{}"s
            )
            << " value" << endl;
}

