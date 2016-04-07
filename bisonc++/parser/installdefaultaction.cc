#include "parser.ih"

void Parser::installDefaultAction(Production const &prod, 
                                  string const &rhs)
{
    Block block;
    block.open(prod.lineNr(), prod.fileName());

    block += "\n"
        "    " + s_semanticValue + " = " + rhs + ";\n"
        "}";

    d_rules.setAction(block);
}
