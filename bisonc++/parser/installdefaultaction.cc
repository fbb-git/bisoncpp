#include "parser.ih"

void Parser::installDefaultAction(Production const &prod, 
                                  string const &rhs)
{
    Block block;
    block.open(prod.lineNr() - 1, prod.fileName());  // account for the newline

    block += "\n"
        "    " + s_semanticValue + " = " + 
                (
                    d_semType == POLYMORPHIC ?
                        "std::move(" + rhs + ")"
                    :
                        rhs 
                ) 
                + ";\n"
        "}";

    d_rules.setAction(block, true);     // true: last actionblock was default
                                        // action. Requires update of the
                                        // action block's line number.
}
