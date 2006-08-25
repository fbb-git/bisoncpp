#include "parser.ih"

void Parser::getType(string *stype) const
{
    *stype = d_scanner.text();

    size_t/*unsigned*/ p1 = stype->find_first_not_of("< \t");
    size_t/*unsigned*/ p2 = stype->find_first_of(" \t>", p1);

    *stype = stype->substr(p1, p2 - p1);
}
