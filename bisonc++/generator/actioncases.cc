#include "generator.ih"

void Generator::actionCases(ostream &out) const
{
    key(out);
    out << '\n';

    vector<Production const *> const &productions = d_rules.productions();

    for_each
    (
        productions.begin(), productions.end(), 
        [&, d_indent](Production const *prod)
        {
            Production::insertAction(prod, out, d_parser.lines(), d_indent);
        }
    );
}







