#include "parser.ih"

bool Parser::warnNegativeIndex(char const *typeOrField, 
                               AtDollar const &atd) const
{
    if (atd.nr() >= 0)
        return false;

    if (not d_negativeDollarIndices)
        wmsg << &d_rules.lastProduction() << ":\n"
            "\tauto " << typeOrField << 
            " ignored for negative $-indices (" << atd.text() << ')' <<
            endl;

    return true;
}
