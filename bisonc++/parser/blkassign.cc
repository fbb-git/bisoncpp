#include "parser.ih"

void Parser::blkAssign(string const &ruleType, Production const &prod)
{
cerr << "blkAssign\n";
    installDefaultAction(
        prod, 
        svsElement(prod.size(), 1) + ".get<Tag__::" + prod[0].sType() + ">()"
    );
}
