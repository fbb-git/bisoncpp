#include "parser.ih"

void Parser::blkDirect(string const &ruleType, Production const &prod)
{
cerr << "blkDirect\n";

    installDefaultAction(
        prod, 
        "std::move(" + svsElement(prod.size(), 1) + ")"
    );
}
