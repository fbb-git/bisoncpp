#include "lookaheadset.ih"

void LookaheadSet::basicLAset(ostream &out) const
{
    out << "    {";

    for (auto const *token: *this)
    {
        if (token->value() != 0)
            out << token << ", ";
    }

    out << "},\n";
}
