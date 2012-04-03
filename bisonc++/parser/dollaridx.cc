#include "parser.ih"

bool Parser::dollarIdx(int idx, size_t nElements) const
{
    if (idx <= static_cast<int>(nElements))
        return true;

    emsg << d_rules.name() << ": refers to element " << idx << ".\n"
            "\tThis rule has " << nElements << " element(s) before "
            "the action block." << endl;

    return false;
}
