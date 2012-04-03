#include "parser.ih"

bool Parser::warnNegativeIndex(int idx, char const *typeOrField) const
{
    if (idx >= 0)
        return false;

    if (not d_negativeDollarIndices)
        wmsg << &d_rules.lastProduction() << ":\n"
            "\tauto " << typeOrField << 
            " associations of negatively indexed elements ($" << idx << 
            ")\n"
            "\tare ignored." << endl;

    return true;
}
