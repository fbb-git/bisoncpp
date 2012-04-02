#include "parser.ih"

void Parser::negativeIndexWarning(int idx) const
{
    if (idx >= 0)
        return;

    if (not d_negativeDollarIndices)
        wmsg << d_rules.name() << ": using negative index $" << idx << endl;
}
