#include "parser.ih"

bool Parser::dollarIdx(int idx, size_t nElements) const
{
    if (idx > static_cast<int>(nElements))
    {
        emsg << d_rules.name() << ": refers to element " << idx << 
            ". This rule has " << nElements << " elements" << 
            endl;
        return false;
    }

    if (not d_negativeDollarIndices)
        wmsg << d_rules.name() << ": ignoring any type/field for element " <<
                idx << endl;

    return true;
}
