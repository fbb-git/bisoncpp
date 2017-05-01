#include "lookaheadset.ih"

bool LookaheadSet::basicLAset(std::ostream &out) const
{
    for (auto const *token: *this)
    {
        if (token->value() != 0)
            out << token << ", ";
    }

    return hasEOF();
}
