#include "parser.ih"

bool Parser::indexTooLarge(int idx, string const &typeSpec, 
                                                    size_t nElements) const
{
    if (idx <= static_cast<int>(nElements))
        return false;

    emsg << d_rules.name() << ": $<" << typeSpec << ">" << idx << 
            " used, but the rule only has " << nElements << " elements" << 
            endl;

    return true;
}
