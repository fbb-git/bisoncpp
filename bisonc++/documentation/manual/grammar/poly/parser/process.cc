#include "parser.ih"

void Parser::process(STYPE_ const &semVal) const
{
    if (semVal.tag() == Tag_::INT)
        cout << "Saw an int-value: " << semVal.get<Tag_::INT>() << '\n';
    else
        cout << "Saw text: " << semVal.get<Tag_::TEXT>() << '\n';
}
