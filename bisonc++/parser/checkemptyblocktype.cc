#include "parser.ih"

void Parser::checkEmptyBlocktype() 
{
    string const &stype = d_rules.sType();

                                    // no type or no default action requested
    if (d_arg.option('N') || stype.empty())
        return;

    Production const &last = d_rules.lastProduction();

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

    wmsg << "rule `" << &last <<
            "': returns default " << stype << " value" << endl;
}

