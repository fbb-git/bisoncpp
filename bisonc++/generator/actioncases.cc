#include "generator.ih"

void Generator::actionCases(ostream &out) const
{
    key(out);
    out << endl;

    vector<Production const *> const &productions = d_rules.productions();

    Arg &arg = Arg::instance();

    Production::IAContext context = {out, arg[0], d_parser.lines(), d_indent};

    for_each
    (
        productions.begin(), productions.end(), 
        FnWrap1c<Production const *, Production::IAContext &>
              (&Production::insertAction, context)
    );
}







