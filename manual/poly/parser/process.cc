#include "parser.ih"

void Parser::process(STYPE__ const &semVal) const
{
    if (semVal.tag() == Tag__::INT)
        cout << "Saw an int-value: " << semVal.get<Tag__::INT>() << '\n';
    else
        cout << "Saw text: " << semVal.get<Tag__::TEXT>() << '\n';
}
