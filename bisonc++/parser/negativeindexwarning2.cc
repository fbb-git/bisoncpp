#include "parser.ih"

bool Parser::negativeIndexWarning(int idx, char const *typeOrField) const
{
    if (idx >= 0)
        return false;

    if (not d_negativeDollarIndices)
        wmsg << d_rules.name() << ": ignoring " << typeOrField << 
            "specifications of "
            "negatively indexed elements ($" << idx << ')' << endl;

    return true;
}
