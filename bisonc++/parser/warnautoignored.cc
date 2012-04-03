#include "parser.ih"

void Parser::warnAutoIgnored(char const *typeOrField, int idx) const
{
    if (not warnNegativeIndex(idx, typeOrField))
    {
        wmsg << &d_rules.lastProduction() << ":\n"
            "\texplicit use of `$";

        if (idx != numeric_limits<int>::max())
            wmsg << idx;
        else
            wmsg << '$';

        wmsg << ".' suppresses auto use of " << typeOrField << " `" << 
            d_rules.sType() << "' of `" << d_rules.name() << "'." << endl;
    }
}
