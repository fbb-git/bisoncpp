#include "generator.ih"

void Generator::actionCases(ostream &out) const
{
    key(out);
    out << '\n';

    vector<Production const *> const &productions = d_rules.productions();

    for_each
    (
        productions.begin(), productions.end(), 
        FnWrap::unary(Production::insertAction, out, d_parser.lines(), 
                                                d_indent)
    );
}







