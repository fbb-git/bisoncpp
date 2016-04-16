#include "parser.ih"

void Parser::installDefaultAction(Production const &prod, 
                                  string const &rhs)
{
    Block block;
    block.open(prod.lineNr() - 1, prod.fileName());  // account for the newline

    block += "\n"
        "    " + s_semanticValue + " = " + rhs + ";\n"
        "}";

    d_rules.setAction(block);
}
